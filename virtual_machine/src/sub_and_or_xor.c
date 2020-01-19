/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_and_or_xor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 18:07:09 by bdudley           #+#    #+#             */
/*   Updated: 2019/11/15 18:07:09 by bdudley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		sub_op(t_info *info, t_processes **prs, t_sdl *sdl)
{
   unsigned char code_arg;
    int           skiped_bytes;
    unsigned char   arg_reg;
    unsigned char   arg_reg2;
    unsigned char   arg_reg3;

    code_arg = ((info->arena)[((*prs)->index + 1) % MEM_SIZE]) & 0xfc;
    if (code_arg == 84)
    {
        arg_reg = *((info->arena) + ((*prs)->index + 2) % MEM_SIZE);
        arg_reg2 = *((info->arena) + ((*prs)->index + 3) % MEM_SIZE);
        arg_reg3 = *((info->arena) + ((*prs)->index + 4) % MEM_SIZE);
        if (arg_reg2 >= 0 && arg_reg2 < REG_NUMBER && arg_reg3 >= 0 && arg_reg3 < REG_NUMBER && arg_reg >= 0 && arg_reg < REG_NUMBER)
        {
            (*prs)->reg[arg_reg3] = (*prs)->reg[arg_reg] - (*prs)->reg[arg_reg2];
            (*prs)->carry = ((*prs)->reg[arg_reg3] == 0) ? 1 : 0;
        }
    }
    skiped_bytes = get_bytes_to_skip(3, code_arg);
    move_cursor((*prs)->index, skiped_bytes, (*prs)->reg[0] - 1, sdl);
    (*prs)->index = ((*prs)->index + skiped_bytes) % MEM_SIZE;
}

void		and_op(t_info *info, t_processes **prs, t_sdl *sdl)
{
	unsigned char code_arg;
	int           skiped_bytes;
	int				flag;
	short int		arg_ind;
	unsigned char   arg_reg;
	int   arg;
	int   arg2;

	flag = 0;
	code_arg = ((info->arena)[((*prs)->index + 1) % MEM_SIZE]) & 0xfc;
	if (code_arg == 84 || code_arg == 100 || code_arg == 116)
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
	else if (code_arg == 148 || code_arg == 164 || code_arg == 180)
	{
		arg = reverse_int(*((int *)((info->arena) + ((*prs)->index + 2) % MEM_SIZE)));
		flag = 4;
	}
	else if (code_arg == 212 || code_arg == 228 || code_arg == 244)
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
			arg2 = (*prs)->reg[arg_reg];
			flag++;
		}
	}
	else if (flag && (code_arg == 100 || code_arg == 228 || code_arg == 164))
	{
		arg2 = reverse_int(*((int *)((info->arena) + ((*prs)->index + 2 + flag) % MEM_SIZE)));
		flag += 4;
	}
	else if (flag && (code_arg == 116 || code_arg == 244 || code_arg == 180))
	{
		arg_ind = reverse_short_int(*((short int *)((info->arena) + ((*prs)->index + 2 + flag ) % MEM_SIZE))) % IDX_MOD;
		arg_ind = get_address(arg_ind % IDX_MOD + (*prs)->index);
		arg2 = reverse_int(*((int *)(info->arena + arg_ind)));
		flag += 2;
	}
	if (flag)
	{
		arg_reg = *((info->arena) + ((*prs)->index + 2 + flag) % MEM_SIZE);
		if (arg_reg >= 0 && arg_reg < REG_NUMBER)
		{
			(*prs)->reg[arg_reg] = arg & arg2;
			(*prs)->carry = ((*prs)->reg[arg_reg] == 0) ? 1 : 0;
		}
	}
	skiped_bytes = get_bytes_to_skip(5, code_arg);
	move_cursor((*prs)->index, skiped_bytes, (*prs)->reg[0] - 1, sdl);
	(*prs)->index = get_address((*prs)->index + skiped_bytes);
}

void		or_op(t_info *info, t_processes **prs, t_sdl *sdl)
{
	unsigned char code_arg;
	int           skiped_bytes;
	int				flag;
	short int		arg_ind;
	unsigned char   arg_reg;
	int   arg;
	int   arg2;

	flag = 0;
	code_arg = ((info->arena)[((*prs)->index + 1) % MEM_SIZE]) & 0xfc;
	if (code_arg == 84 || code_arg == 100 || code_arg == 116)
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
	else if (code_arg == 148 || code_arg == 164 || code_arg == 180)
	{
		arg = reverse_int(*((int *)((info->arena) + ((*prs)->index + 2) % MEM_SIZE)));
		flag = 4;
	}
	else if (code_arg == 212 || code_arg == 228 || code_arg == 244)
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
			arg2 = (*prs)->reg[arg_reg];
			flag++;
		}
	}
	else if (flag && (code_arg == 100 || code_arg == 228 || code_arg == 164))
	{
		arg2 = reverse_int(*((int *)((info->arena) + ((*prs)->index + 2 + flag) % MEM_SIZE)));
		flag += 4;
	}
	else if (flag && (code_arg == 116 || code_arg == 244 || code_arg == 180))
	{
		arg_ind = reverse_short_int(*((short int *)((info->arena) + ((*prs)->index + 2 + flag ) % MEM_SIZE))) % IDX_MOD;
		arg_ind = get_address(arg_ind % IDX_MOD + (*prs)->index);
		arg2 = reverse_int(*((int *)(info->arena + arg_ind)));
		flag += 2;
	}
	if (flag)
	{
		arg_reg = *((info->arena) + ((*prs)->index + 2 + flag) % MEM_SIZE);
		if (arg_reg >= 0 && arg_reg < REG_NUMBER)
		{
			(*prs)->reg[arg_reg] = arg | arg2;
			(*prs)->carry = ((*prs)->reg[arg_reg] == 0) ? 1 : 0;
		}
	}
	skiped_bytes = get_bytes_to_skip(5, code_arg);
	move_cursor((*prs)->index, skiped_bytes, (*prs)->reg[0] - 1, sdl);
	(*prs)->index = get_address((*prs)->index + skiped_bytes);
}

void		xor_op(t_info *info, t_processes **prs, t_sdl *sdl)
{
	unsigned char code_arg;
	int           skiped_bytes;
	int				flag;
	short int		arg_ind;
	unsigned char   arg_reg;
	int   arg;
	int   arg2;

	flag = 0;
	code_arg = ((info->arena)[((*prs)->index + 1) % MEM_SIZE]) & 0xfc;
	if (code_arg == 84 || code_arg == 100 || code_arg == 116)
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
	else if (code_arg == 148 || code_arg == 164 || code_arg == 180)
	{
		arg = reverse_int(*((int *)((info->arena) + ((*prs)->index + 2) % MEM_SIZE)));
		flag = 4;
	}
	else if (code_arg == 212 || code_arg == 228 || code_arg == 244)
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
			arg2 = (*prs)->reg[arg_reg];
			flag++;
		}
	}
	else if (flag && (code_arg == 100 || code_arg == 228 || code_arg == 164))
	{
		arg2 = reverse_int(*((int *)((info->arena) + ((*prs)->index + 2 + flag) % MEM_SIZE)));
		flag += 4;
	}
	else if (flag && (code_arg == 116 || code_arg == 244 || code_arg == 180))
	{
		arg_ind = reverse_short_int(*((short int *)((info->arena) + ((*prs)->index + 2 + flag ) % MEM_SIZE))) % IDX_MOD;
		arg_ind = get_address(arg_ind % IDX_MOD + (*prs)->index);
		arg2 = reverse_int(*((int *)(info->arena + arg_ind)));
		flag += 2;
	}
	if (flag)
	{
		arg_reg = *((info->arena) + ((*prs)->index + 2 + flag) % MEM_SIZE);
		if (arg_reg >= 0 && arg_reg < REG_NUMBER)
		{
			(*prs)->reg[arg_reg] = arg ^ arg2;
			(*prs)->carry = ((*prs)->reg[arg_reg] == 0) ? 1 : 0;
		}
	}
	skiped_bytes = get_bytes_to_skip(5, code_arg);
	move_cursor((*prs)->index, skiped_bytes, (*prs)->reg[0] - 1, sdl);
	(*prs)->index = get_address((*prs)->index + skiped_bytes);
}