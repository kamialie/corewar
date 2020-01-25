/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lld_lldi_lfork_aff.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 18:10:13 by bdudley           #+#    #+#             */
/*   Updated: 2019/12/28 18:04:44 by bdudley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void				lld_op(t_info *info, t_processes **prs, t_sdl *sdl)
{
	unsigned char	code_arg;
	short int		current_location;
	short int		shift;
	int				value;

	shift = 2;
	current_location = (*prs)->index;
	code_arg = ((info->arena)[(current_location + 1) % MEM_SIZE]) & 0xf0;
	if (code_arg == 208 || code_arg == 144)
	{
		if (code_arg == 208)
			shift += get_T_IND(current_location, shift, info->arena, 0);
		value = get_T_DIR(current_location, shift, info->arena);
		shift = (code_arg == 208) ? 2 : 4;
		set_T_REG(value, shift, info->arena, prs);
	}
	shift_next_op(code_arg, 12, prs, sdl);
}

void				lldi_op(t_info *info, t_processes **prs, t_sdl *sdl)
{
	unsigned char	code_arg;
	unsigned char	arg_reg;
	short int		current_location;
	short int		shift;
	int				value;

	shift = 2;
	current_location = (*prs)->index;
	code_arg = ((info->arena)[(current_location+ 1) % MEM_SIZE]) & 0xfc;
	value = get_arg((code_arg >> 6) & 0x3, &shift, info->arena, prs);
	if ((shift - 2) && (code_arg == 84 || code_arg == 212 || code_arg == 148 ||
						code_arg == 100 || code_arg == 228 || code_arg == 164))
		value += get_arg((code_arg >> 4) & 0x3, &shift, info->arena, prs);
	if (shift + 3 == get_bytes_to_skip(9, code_arg))
	{
		arg_reg = *((info->arena) + (current_location + shift) % MEM_SIZE);
		if (arg_reg >= 0 && arg_reg < REG_NUMBER)
		{
			value = get_address(current_location + value);
			ft_memcpy((*prs)->reg + arg_reg, info->arena + value, 4);
			(*prs)->reg[arg_reg] = reverse_int((*prs)->reg[arg_reg]);
		}
	}
	shift_next_op(code_arg, 13, prs, sdl);
}

void				lfork_op(t_info *info, t_processes **prs, t_sdl *sdl)
{
	short int		current_location;
	short int		num_player;
	short int		arg;
	int				i;

	current_location = (*prs)->index;
	num_player = ((*prs)->reg)[0];
	arg = get_T_IND(current_location, 1, info->arena, 0);
	add_elem(&(info->processes), arg, num_player);
	info->processes->carry = (*prs)->carry;
	(info->processes)->cc_live = (*prs)->cc_live;
	i = -1;
	while (++i < REG_NUMBER)
		(info->processes)->reg[i] = (*prs)->reg[i];
	move_cursor((*prs)->index, 3, IND(num_player), sdl);
	(*prs)->index = get_address((current_location + 3));
	create_cursor(arg, IND(num_player), sdl);
}

void				aff_op(t_info *info, t_processes **prs, t_sdl *sdl)
{
	unsigned char code_arg;

	code_arg = ((info->arena)[((*prs)->index + 1) % MEM_SIZE]) & 0xc0;
	if (code_arg == 64)
	{
		code_arg = *((info->arena) + ((*prs)->index + 2) % MEM_SIZE);
		if (code_arg >= 0 && code_arg < REG_NUMBER)
		{
			printf("Aff : %c\n", (*prs)->reg[code_arg]);
		}
		move_cursor((*prs)->index, 3, IND((*prs)->reg[0]), sdl);
		(*prs)->index = (((*prs)->index) + 3) % MEM_SIZE;
	}
}
