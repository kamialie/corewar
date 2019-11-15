/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gladiatorial_fight.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 17:20:05 by bdudley           #+#    #+#             */
/*   Updated: 2019/11/15 17:35:48 by bdudley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		take_actions(t_processes *prs)
{
	if (prs->cc_op == 0)  //получаем код следущей операции и если она валидна записываем количество циклов
	{
		prs->code_op = *(prs->ptr);
		if (*(prs->ptr) > 0 && *(prs->ptr) < 17)
			prs->cc_op = g_op_tab[prs->code_op - 1].cycle_for_exec;
	}
	if (prs->cc_op > 0) //уменьшаем количество циклов ожидания
		--prs->cc_op;
	if (prs->cc_op == 0) //выполняем операцию
	{
		if (*(prs->ptr) > 0 && *(prs->ptr) < 17)
		{
		}
		else
			prs->ptr++;
	}
}

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
	int 		i;
	int			check;
	t_processes	*prs;

	check = 0;
	prs = info->processes;
	while (info->processes)
	{
		i = -1;
		while (++i <= info->cycle_to_die)
		{
			while (prs)
			{
				take_actions(prs);
				prs = prs->next;
			}
			++info->count_cycles;
		}
		kick_noobs(info, &check);
	}
}