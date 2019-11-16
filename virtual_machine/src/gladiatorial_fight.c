/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gladiatorial_fight.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 17:20:05 by bdudley           #+#    #+#             */
/*   Updated: 2019/11/16 20:34:20 by bdudley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		take_actions(t_info *info, t_processes *prs)
{
	if (prs->cc_op == 0)  //получаем код следущей операции и если она валидна записываем количество циклов
	{
		prs->code_op = (info->arena)[prs->index];
		if ((info->arena)[prs->index] > 0 && (info->arena)[prs->index] < 17)
			prs->cc_op = g_op_tab[prs->code_op - 1].cycle_for_exec;
	}
	if (prs->cc_op > 0) //уменьшаем количество циклов ожидания
		--prs->cc_op;
	if (prs->cc_op == 0) //выполняем операцию
	{
		//Если операция валидна, то вызываем исполняющую ее функцию
		//Иначе смещаем на 1 байт
		if ((info->arena)[prs->index] >= 0 && (info->arena)[prs->index] < 17)
			g_op_tab[IND((info->arena)[prs->index])].func(info, &prs);
		else
			prs->index = ++(prs->index) % MEM_SIZE;
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
	while (info->processes)
	{
		i = -1;
		while (++i <= info->cycle_to_die)
		{
			prs = info->processes;
			while (prs)
			{
				take_actions(info, prs);
				prs = prs->next;
			}
			++info->count_cycles;
		}
		kick_noobs(info, &check);
	}
}