/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live_ld_st_add.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 18:05:20 by bdudley           #+#    #+#             */
/*   Updated: 2019/11/17 18:06:45 by bdudley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		live_op(t_info *info, t_processes **prs, t_sdl *sdl)
{
	int 	num_player;
	int     arg;
	int     new_location;

    printf("live\n");
	(*prs)->cc_live = info->count_cycles;
	num_player = (info->arena)[(*prs)->index];
	arg = (info->arena)[(*prs)->index + 1];
	if (((info->players)[num_player - 1]).magic == COREWAR_EXEC_MAGIC && arg == (*prs)->reg[0])
		info->last_live = num_player;
	new_location = (((*prs)->index) + 5) % MEM_SIZE;
	move_cursor((*prs)->index, new_location, num_player - 1, sdl);
    (*prs)->index = new_location; //1 байт занимает код операции и 4 байта занимает аргумент
	//printf("cc_live %d\n./", (*prs)->cc_live);




}

void		ld_op(t_info *info, t_processes **prs, t_sdl *sdl)
{

}

void		st_op(t_info *info, t_processes **prs, t_sdl *sdl)
{

}

void		add_op(t_info *info, t_processes **prs, t_sdl *sdl)
{

}