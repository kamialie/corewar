/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live_ld_st_add.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 18:05:20 by bdudley           #+#    #+#             */
/*   Updated: 2019/12/14 17:00:40 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		live_op(t_info *info, t_processes **prs, t_sdl *sdl)
{
	int     arg;
	int     new_location;

    printf("live\n");
	(*prs)->cc_live = info->count_cycles;
	arg = (info->arena)[((*prs)->index + 1) % MEM_SIZE];
	if (arg == (*prs)->reg[0])
		info->last_live = (*prs)->reg[0];
	new_location = (((*prs)->index) + 5) % MEM_SIZE;
	//create_cursor(info->arena[new_location], new_location, (*prs)->reg[0] - 1, sdl);
	//update_byte(info->arena[(*prs)->index], (*prs)->index, (*prs)->reg[0] - 1, sdl);
	move_cursor((*prs)->index, 5, (*prs)->reg[0] - 1, sdl);
    (*prs)->index = new_location; //1 байт занимает код операции и 4 байта занимает аргумент
	//printf("cc_live %d\n./", (*prs)->cc_live);
}

void		ld_op(t_info *info, t_processes **prs, t_sdl *sdl)
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
        arg_ind = reverse_short_int(*((short int *)((info->arena) + ((*prs)->index + 2) % MEM_SIZE))) % IDX_MOD;
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
    printf("%d \n", (*prs)->reg[1]);
}

void		st_op(t_info *info, t_processes **prs, t_sdl *sdl)
{
    unsigned char code_arg;
    unsigned char   arg_reg;
    int           skiped_bytes;
    unsigned char   arg_reg2;
    short int     arg_ind;
    int             i;

    code_arg = ((info->arena)[((*prs)->index + 1) % MEM_SIZE]) & 0xf0;
    if (code_arg == 112 || code_arg == 80)
    {
        arg_reg = *((info->arena) + ((*prs)->index + 2) % MEM_SIZE);
        if (arg_reg >= 0 && arg_reg < REG_NUMBER) {
            if (code_arg == 80)
            {
                arg_reg2 = *((info->arena) + ((*prs)->index + 3) % MEM_SIZE);
                if (arg_reg2 >= 0 && arg_reg2 < REG_NUMBER)
                {
                    (*prs)->reg[arg_reg2] = (*prs)->reg[arg_reg];
                }
            }
            else
            {
                arg_ind = reverse_short_int(*((short int *)((info->arena) + ((*prs)->index + 3) % MEM_SIZE))) % IDX_MOD;
                arg_ind = get_address(arg_ind + (*prs)->index);
                ft_memcpy((info->arena) + arg_ind, (*prs)->reg + arg_reg, 4);
                update_bytes(arg_ind, 4, (*prs)->reg[0] - 1, sdl);
            }
        }

    }
    skiped_bytes = get_bytes_to_skip(2, code_arg);
    move_cursor((*prs)->index, skiped_bytes, (*prs)->reg[0] - 1, sdl);
    (*prs)->index = ((*prs)->index + skiped_bytes) % MEM_SIZE;
}

void		add_op(t_info *info, t_processes **prs, t_sdl *sdl)
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
            (*prs)->reg[arg_reg3] = (*prs)->reg[arg_reg] + (*prs)->reg[arg_reg2];
            (*prs)->carry = ((*prs)->reg[arg_reg3] == 0) ? 1 : 0;
        }
    }
    skiped_bytes = get_bytes_to_skip(3, code_arg);
    move_cursor((*prs)->index, skiped_bytes, (*prs)->reg[0] - 1, sdl);
    (*prs)->index = ((*prs)->index + skiped_bytes) % MEM_SIZE;
}
