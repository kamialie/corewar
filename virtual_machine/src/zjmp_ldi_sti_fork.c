/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp_ldi_sti_fork.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 18:08:19 by bdudley           #+#    #+#             */
/*   Updated: 2019/11/17 20:31:51 by bdudley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		zjmp_op(t_info *info, t_processes **prs, t_sdl *sdl)
{
	printf("zjmp\n");
	if ((*prs)->carry)
	{
		(*prs)->index = (*prs)->index + *((int *)(info->arena + (*prs)->index + 1)) % IDX_MOD;
	}
	(*prs)->index = (((*prs)->index) + 3) % MEM_SIZE; //1 байт занимает код операции и 2 байта занимает аргумент
}

void		ldi_op(t_info *info, t_processes **prs, t_sdl *sdl)
{

}

void		sti_op(t_info *info, t_processes **prs, t_sdl *sdl)
{

}

void		fork_op(t_info *info, t_processes **prs, t_sdl *sdl)
{
	short	int 	*ptr;
	int             i;

	//ptr = (short int *)(1365 + 1 + info->arena);
	//printf("%d\n", ((*prs)->index));
	printf("fork %d\n", 0);
//	add_elem(&(info->processes), *((int *)(info->arena + ((*prs)->index + 1) % MEM_SIZE)) % IDX_MOD, ((*prs)->reg)[0]);
//	info->processes->carry = (*prs)->carry;
//	(info->processes)->cc_live = (*prs)->cc_live;
//	i = -1;
//	while (++i < REG_NUMBER)
//        (info->processes)->reg[i] = (*prs)->reg[i];
    short int current_location = (*prs)->index;
	(*prs)->index = (((*prs)->index) + 3) % MEM_SIZE; //1 байт занимает код операции и 2 байта занимает аргумент
    //printf("%d color", (*prs)->reg[0]);
	move_cursor(current_location, (*prs)->index, (*prs)->reg[0] - 1, sdl);
    SDL_UpdateWindowSurface(sdl->window);
   // create_cursor(info->processes->index, info->processes->reg[0], sdl);
}
