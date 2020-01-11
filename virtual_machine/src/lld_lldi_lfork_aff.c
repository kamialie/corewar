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
//    create_cursor(info->arena[((*prs)->index + 1) % MEM_SIZE], ((*prs)->index + 1) % MEM_SIZE, (*prs)->reg[0] - 1, sdl);
//    update_byte(info->arena[(*prs)->index], (*prs)->index, (*prs)->reg[0] - 1, sdl);
//    (*prs)->index = (++((*prs)->index)) % MEM_SIZE;
}

void		lldi_op(t_info *info, t_processes **prs, t_sdl *sdl)
{
//    create_cursor(info->arena[((*prs)->index + 1) % MEM_SIZE], ((*prs)->index + 1) % MEM_SIZE, (*prs)->reg[0] - 1, sdl);
//update_byte(info->arena[(*prs)->index], (*prs)->index, (*prs)->reg[0] - 1, sdl);
//(*prs)->index = (++((*prs)->index)) % MEM_SIZE;
}

void		lfork_op(t_info *info, t_processes **prs, t_sdl *sdl)
{
    short	int 	*ptr;
    unsigned short   int     arg;
    short   int     current_location;
    int             i;


    current_location = (*prs)->index;
    arg = reverse_short_int(current_location + *((unsigned short int *)(info->arena + (current_location + 1) % MEM_SIZE)));
    arg %= MEM_SIZE;
    add_elem(&(info->processes), arg, ((*prs)->reg)[0]);
    info->processes->carry = (*prs)->carry;
    (info->processes)->cc_live = (*prs)->cc_live;
    i = -1;
    while (++i < REG_NUMBER)
        (info->processes)->reg[i] = (*prs)->reg[i];
    move_cursor((*prs)->index, 3, (*prs)->reg[0] - 1, sdl);
    (*prs)->index = (((*prs)->index) + 3) % MEM_SIZE; //1 байт занимает код операции и 2 байта занимает аргумент
    create_cursor(arg, (*prs)->reg[0] - 1, sdl);
}

void		aff_op(t_info *info, t_processes **prs, t_sdl *sdl)
{
    unsigned char code_arg;

    printf("aaa\n");
    code_arg = *((info->arena) + ((*prs)->index + 1) % MEM_SIZE);
    (*prs)->reg[code_arg] = 65;
    if (code_arg >= 0 && code_arg < REG_NUMBER)
    {
        printf("Aff : %c\n", (*prs)->reg[code_arg]);
    }
    (*prs)->index = (((*prs)->index) + 2) % MEM_SIZE;
}
