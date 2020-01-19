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

void		lld_op(t_info *info, t_processes **prs, t_sdl *sdl)
{
    unsigned char code_arg;
    unsigned char   arg_reg;
    int           skiped_bytes;
    int           arg_dir;
    short int     arg_ind;

    printf("ld \n");
    code_arg = ((info->arena)[((*prs)->index + 1) % MEM_SIZE]) & 0xf0;
    if (code_arg == 208) //ind
    {
        printf("ind \n");
        arg_ind = reverse_short_int(*((short int *)((info->arena) + ((*prs)->index + 2) % MEM_SIZE)));
        arg_ind = get_address(arg_ind + (*prs)->index);
        arg_dir = reverse_int(*((int *)((info->arena) + arg_ind % MEM_SIZE)));
        arg_reg = *((info->arena) + ((*prs)->index + 4) % MEM_SIZE);
        if (arg_reg >= 0 && arg_reg < REG_NUMBER)
        {
            (*prs)->reg[arg_reg] = arg_dir; //может можно без приведения
            (*prs)->carry = (arg_dir == 0) ? 1 : 0;
        }
    }
    else if (code_arg == 144) //dir
    {
        printf("dir \n");
        arg_dir = reverse_int(*((int *)((info->arena) + ((*prs)->index + 2) % MEM_SIZE))); //код операции + код аргументов
        arg_reg = *((info->arena) + ((*prs)->index + 6) % MEM_SIZE);
        if (arg_reg >= 0 && arg_reg < REG_NUMBER)
        {
            (*prs)->reg[arg_reg] = arg_dir; //может можно без приведения
            (*prs)->carry = (arg_dir == 0) ? 1 : 0;
        }
    }
    skiped_bytes = get_bytes_to_skip(1, code_arg);
    move_cursor((*prs)->index, skiped_bytes, (*prs)->reg[0] - 1, sdl);
    (*prs)->index = ((*prs)->index + skiped_bytes) % MEM_SIZE;
}

void		lldi_op(t_info *info, t_processes **prs, t_sdl *sdl)
{
	unsigned char code_arg;
	int           skiped_bytes;
	int				flag;
	short int		arg_ind;
	unsigned char   arg_reg;
	int   arg;

	printf("ldi\n");
	flag = 0;
	code_arg = ((info->arena)[((*prs)->index + 1) % MEM_SIZE]) & 0xfc;
	if (code_arg == 84 || code_arg == 100)
	{
		arg_reg = *((info->arena) + ((*prs)->index + 2) % MEM_SIZE);
		if (arg_reg < 0 && arg_reg >= REG_NUMBER)
			flag = 0;
		else
		{
			arg = (*prs)->reg[arg_reg];
			flag = 1;
		}
	}
	else if (code_arg == 148 || code_arg == 164)
	{
		arg = reverse_short_int(*((short int *)((info->arena) + ((*prs)->index + 2) % MEM_SIZE)));
		flag = 2;
	}
	else if (code_arg == 212 || code_arg == 228)
	{
		arg_ind = reverse_short_int(*((short int *)((info->arena) + ((*prs)->index + 2) % MEM_SIZE))) % IDX_MOD;
		arg_ind = get_address(arg_ind % IDX_MOD + (*prs)->index);
	    arg = reverse_int(*((int *)(info->arena + arg_ind)));
		flag = 2;
	}
	if (flag && (code_arg == 84 || code_arg == 212 || code_arg == 148))
	{
		arg_reg = *((info->arena) + ((*prs)->index + 2 + flag) % MEM_SIZE);
		if (arg_reg < 0 && arg_reg >= REG_NUMBER)
			flag = 0;
		else
		{
			arg += (*prs)->reg[arg_reg];
			flag++;
		}
	}
	else if (flag && (code_arg == 100 || code_arg == 228 || code_arg == 164))
	{
		arg += reverse_short_int(*((short int *)((info->arena) + ((*prs)->index + 2 + flag) % MEM_SIZE)));
		flag += 2;
	}
	if (flag)
	{
		arg_reg = *((info->arena) + ((*prs)->index + 2 + flag) % MEM_SIZE);
		if (arg_reg >= 0 && arg_reg < REG_NUMBER)
		{
			arg = get_address((*prs)->index + arg);
			ft_memcpy((*prs)->reg + arg_reg, info->arena + arg, 4);
			(*prs)->reg[arg_reg] = reverse_int((*prs)->reg[arg_reg]);
		}
	}
	skiped_bytes = get_bytes_to_skip(13, code_arg);
	move_cursor((*prs)->index, skiped_bytes, (*prs)->reg[0] - 1, sdl);
	(*prs)->index = get_address((*prs)->index + skiped_bytes);
}

void		lfork_op(t_info *info, t_processes **prs, t_sdl *sdl)
{
    short	int 	*ptr;
    unsigned short   int     arg;
    short   int     current_location;
    int             i;


    current_location = (*prs)->index;
    arg = reverse_short_int(current_location + *((short int *)(info->arena + (current_location + 1) % MEM_SIZE)));
    arg %= MEM_SIZE;
    add_elem(&(info->processes), arg, ((*prs)->reg)[0]);
    info->processes->carry = (*prs)->carry;
    (info->processes)->cc_live = (*prs)->cc_live;
    i = -1;
    while (++i < REG_NUMBER)
        (info->processes)->reg[i] = (*prs)->reg[i];
    move_cursor((*prs)->index, 3, (*prs)->reg[0] - 1, sdl);
    (*prs)->index = get_address(((*prs)->index) + 3); //1 байт занимает код операции и 2 байта занимает аргумент
    create_cursor(arg, (*prs)->reg[0] - 1, sdl);
}

void		aff_op(t_info *info, t_processes **prs, t_sdl *sdl)
{
    unsigned char code_arg;


    code_arg = ((info->arena)[((*prs)->index + 1) % MEM_SIZE]) & 0xc0;
    if (code_arg == 64)
    {
        code_arg = *((info->arena) + ((*prs)->index + 2) % MEM_SIZE);
        if (code_arg >= 0 && code_arg < REG_NUMBER) {
            printf("Aff : %c\n", (*prs)->reg[code_arg]);
        }
        move_cursor((*prs)->index, 3, (*prs)->reg[0] - 1, sdl);
        (*prs)->index = (((*prs)->index) + 3) % MEM_SIZE;
    }
}
