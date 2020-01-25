/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp_ldi_sti_fork.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 18:08:19 by bdudley           #+#    #+#             */
/*   Updated: 2019/12/28 18:06:13 by bdudley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void				zjmp_op(t_info *info, t_processes **prs, t_sdl *sdl)
{
	short int		current_location;
	short int		shift;

	current_location = (*prs)->index;
	shift = 3;
	if ((*prs)->carry)
		shift = get_t_ind(current_location, 1, info->arena, 1);
	(*prs)->index = get_address(shift + current_location);
	if (sdl != NULL)
		move_cursor(current_location, shift, IND((*prs)->reg[0]), sdl);
}

void				ldi_op(t_info *info, t_processes **prs, t_sdl *sdl)
{
	unsigned char	code_arg;
	unsigned char	arg_reg;
	short int		current_location;
	short int		shift;
	int				value;

	shift = 2;
	current_location = (*prs)->index;
	code_arg = ((info->arena)[(current_location + 1) % MEM_SIZE]) & 0xfc;
	value = get_arg((code_arg >> 6) & 0x3, &shift, info->arena, prs);
	if ((shift - 2) && (code_arg == 84 || code_arg == 212 || code_arg == 148 ||
				code_arg == 100 || code_arg == 228 || code_arg == 164))
		value += get_arg((code_arg >> 4) & 0x3, &shift, info->arena, prs);
	if (shift + 3 == get_bytes_to_skip(9, code_arg))
	{
		arg_reg = *((info->arena) + (current_location + shift) % MEM_SIZE);
		if (arg_reg >= 0 && arg_reg < REG_NUMBER)
		{
			value = get_address((current_location + value) % IDX_MOD);
			ft_memcpy((*prs)->reg + arg_reg, info->arena + value, 4);
			(*prs)->reg[arg_reg] = reverse_int((*prs)->reg[arg_reg]);
		}
	}
	shift_next_op(code_arg, 9, prs, sdl);
}

void				sti_op(t_info *info, t_processes **prs, t_sdl *sdl)
{
	unsigned char	code_arg;
	unsigned char	arg_reg;
	short int		current_location;
	short int		shift;
	int				value;

	shift = 2;
	current_location = (*prs)->index;
	code_arg = ((info->arena)[(current_location + 1) % MEM_SIZE]) & 0xfc;
	value = get_arg((code_arg >> 6) & 0x3, &shift, info->arena, prs);
	if ((shift - 2) && (code_arg == 84 || code_arg == 212 || code_arg == 148 ||
						code_arg == 100 || code_arg == 228 || code_arg == 164))
		value += get_arg((code_arg >> 4) & 0x3, &shift, info->arena, prs);
	if (shift + 3 == get_bytes_to_skip(10, code_arg))
	{
		arg_reg = *((info->arena) + (current_location + shift) % MEM_SIZE);
		if (arg_reg >= 0 && arg_reg < REG_NUMBER)
		{
			value = get_address((current_location + value) % IDX_MOD);
			ft_memcpy(info->arena + value, (*prs)->reg + arg_reg, 4);
			if (sdl != NULL)
				update_bytes(value, 4, IND((*prs)->reg[0]), sdl);
		}
	}
	shift_next_op(code_arg, 10, prs, sdl);
}

void				fork_op(t_info *info, t_processes **prs, t_sdl *sdl)
{
	short int current_location;
	short int num_player;
	short int arg;
	int i;

	current_location = (*prs)->index;
	num_player = ((*prs)->reg)[0];
	arg = get_t_ind(current_location, 1, info->arena, 1);
	arg = get_address(arg);
	add_elem(&(info->processes), arg, num_player);
	info->processes->carry = (*prs)->carry;
	(info->processes)->cc_live = (*prs)->cc_live;
	i = -1;
	while (++i < REG_NUMBER)
		(info->processes)->reg[i] = (*prs)->reg[i];
	if (sdl != NULL)
	{
		move_cursor((*prs)->index, 3, IND(num_player), sdl);
		create_cursor(arg, IND(num_player), sdl);
		Mix_PlayChannel(-1, sdl->birth_effect, 0);
	}
	(*prs)->index = get_address((current_location + 3));
}
