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

void		live_op(t_info *info, t_processes **prs)
{
	int 	num_player;

	printf("live\n");
	(*prs)->cc_live = info->count_cycles;
	num_player = (info->arena)[(*prs)->index];
	if (((info->players)[num_player - 1]).magic == COREWAR_EXEC_MAGIC)
		info->last_live = num_player;
	(*prs)->index = (((*prs)->index) + 5) % MEM_SIZE; //1 байт занимает код операции и 4 байта занимает аргумент
}

void		ld_op(t_info *info, t_processes **prs)
{

}

void		st_op(t_info *info, t_processes **prs)
{

}

void		add_op(t_info *info, t_processes **prs)
{

}