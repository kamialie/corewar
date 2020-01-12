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

void		zjmp_op(t_info *info, t_processes **prs, t_sdl *sdl)
{
    unsigned short int     current_location;
    short int     shift;
    current_location = (*prs)->index;
    shift = 2;
	if ((*prs)->carry)
	{
        shift = reverse_short_int(*((short int *)(info->arena + (current_location + 1) % MEM_SIZE)));
        shift = shift % IDX_MOD;
    }
	printf("!!!shift %d\n", shift);
	(*prs)->index = (current_location + shift) % MEM_SIZE; //1 байт занимает код операции и 2 байта занимает аргумент
    move_cursor(current_location, shift , (*prs)->reg[0] - 1, sdl);
}

void		ldi_op(t_info *info, t_processes **prs, t_sdl *sdl)
{
//    create_cursor(info->arena[((*prs)->index + 1) % MEM_SIZE], ((*prs)->index + 1) % MEM_SIZE, (*prs)->reg[0] - 1, sdl);
//    update_byte(info->arena[(*prs)->index], (*prs)->index, (*prs)->reg[0] - 1, sdl);
//    (*prs)->index = (++((*prs)->index)) % MEM_SIZE;
}

void		sti_op(t_info *info, t_processes **prs, t_sdl *sdl)
{
//    create_cursor(info->arena[((*prs)->index + 1) % MEM_SIZE], ((*prs)->index + 1) % MEM_SIZE, (*prs)->reg[0] - 1, sdl);
//    update_byte(info->arena[(*prs)->index], (*prs)->index, (*prs)->reg[0] - 1, sdl);
//    (*prs)->index = (++((*prs)->index)) % MEM_SIZE;
}

void		fork_op(t_info *info, t_processes **prs, t_sdl *sdl)
{
	short	int 	*ptr;
	unsigned short   int     arg;
    short   int     current_location;
	int             i;


    current_location = (*prs)->index;
	arg = reverse_short_int(*((unsigned short int *)(info->arena + (current_location + 1) % MEM_SIZE)));
	arg %= IDX_MOD;
    //printf("fork %u\n", arg);
	add_elem(&(info->processes), arg, ((*prs)->reg)[0]);
	info->processes->carry = (*prs)->carry;
	(info->processes)->cc_live = (*prs)->cc_live;
	i = -1;
	while (++i < REG_NUMBER)
        (info->processes)->reg[i] = (*prs)->reg[i];
	//create_cursor(arg, (current_location + 1) % MEM_SIZE, (*prs)->reg[0] - 1, sdl);
    //create_cursor(info->arena[(*prs)->index], (*prs)->index, (*prs)->reg[0] - 1, sdl);
    //update_byte(info->arena[current_location], current_location, (*prs)->reg[0] - 1, sdl);
	move_cursor((*prs)->index, 3, (*prs)->reg[0] - 1, sdl);
	(*prs)->index = (((*prs)->index) + 3) % MEM_SIZE; //1 байт занимает код операции и 2 байта занимает аргумент
    create_cursor(arg, (*prs)->reg[0] - 1, sdl);
}
