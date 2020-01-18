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
//    create_cursor(info->arena[((*prs)->index + 1) % MEM_SIZE], ((*prs)->index + 1) % MEM_SIZE, (*prs)->reg[0] - 1, sdl);
//    update_byte(info->arena[(*prs)->index], (*prs)->index, (*prs)->reg[0] - 1, sdl);
//    (*prs)->index = (++((*prs)->index)) % MEM_SIZE;
}

void		or_op(t_info *info, t_processes **prs, t_sdl *sdl)
{
//    create_cursor(info->arena[((*prs)->index + 1) % MEM_SIZE], ((*prs)->index + 1) % MEM_SIZE, (*prs)->reg[0] - 1, sdl);
//    update_byte(info->arena[(*prs)->index], (*prs)->index, (*prs)->reg[0] - 1, sdl);
//    (*prs)->index = (++((*prs)->index)) % MEM_SIZE;
}

void		xor_op(t_info *info, t_processes **prs, t_sdl *sdl)
{
//    create_cursor(info->arena[((*prs)->index + 1) % MEM_SIZE], ((*prs)->index + 1) % MEM_SIZE, (*prs)->reg[0] - 1, sdl);
//    update_byte(info->arena[(*prs)->index], (*prs)->index, (*prs)->reg[0] - 1, sdl);
//    (*prs)->index = (++((*prs)->index)) % MEM_SIZE;
}