/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp_ldi_sti_fork.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 18:08:19 by bdudley           #+#    #+#             */
/*   Updated: 2019/12/14 16:41:40 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		zjmp_op(t_info *info, t_processes **prs, t_sdl *sdl)
{
//	printf("zjmp\n");
//	if ((*prs)->carry)
//	{
//		(*prs)->index = (*prs)->index + *((int *)(info->arena + (*prs)->index + 1)) % IDX_MOD;
//	}
//	(*prs)->index = (((*prs)->index) + 3) % MEM_SIZE; //1 байт занимает код операции и 2 байта занимает аргумент
//    create_cursor(info->arena[((*prs)->index + 1) % MEM_SIZE], ((*prs)->index + 1) % MEM_SIZE, (*prs)->reg[0] - 1, sdl);
//    update_byte(info->arena[(*prs)->index], (*prs)->index, (*prs)->reg[0] - 1, sdl);
//    (*prs)->index = (++((*prs)->index)) % MEM_SIZE;
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
	short   int     arg;
    short   int     current_location;
	int             i;

	printf("fork %d\n", 0);
    current_location = (*prs)->index;
	arg = info->arena[(current_location + 1) % MEM_SIZE];
	add_elem(&(info->processes), arg, ((*prs)->reg)[0]);
	info->processes->carry = (*prs)->carry;
	(info->processes)->cc_live = (*prs)->cc_live;
	i = -1;
	while (++i < REG_NUMBER)
        (info->processes)->reg[i] = (*prs)->reg[i];
	(*prs)->index = (((*prs)->index) + 3) % MEM_SIZE; //1 байт занимает код операции и 2 байта занимает аргумент
	create_cursor(arg, (current_location + 1) % MEM_SIZE, (*prs)->reg[0] - 1, sdl);
    create_cursor(info->arena[(*prs)->index], (*prs)->index, (*prs)->reg[0] - 1, sdl);
    update_byte(info->arena[current_location], current_location, (*prs)->reg[0] - 1, sdl);
}
