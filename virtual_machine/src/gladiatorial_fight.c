/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gladiatorial_fight.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 17:20:05 by bdudley           #+#    #+#             */
/*   Updated: 2019/11/13 20:30:34 by bdudley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		kick_noobs(t_info *info, int *check)
{
	t_processes		*ptr;


	ptr = info->processes;
	while (ptr)
	{
		if (info->count_cycles - ptr->cc_live > info->cycle_to_die)
			delete_elem(&ptr, info);
		else
			ptr = ptr->next;
	}
	if (info->count_live >= NBR_LIVE || *check < MAX_CHECKS)
	{
		*check = -1;
		info->cycle_to_die -= CYCLE_DELTA;
	}
	++(*check);
	info->count_live = 0;
	++info->count_check;
}

void		gladiatorial_fight(t_info *info)
{
	int 	i;
	int		check;

	check = 0;
	while (info->processes)
	{
		i = -1;
		while (++i <= info->cycle_to_die)
		{
			++info->count_cycles;
		}
		kick_noobs(info, &check);
	}
}