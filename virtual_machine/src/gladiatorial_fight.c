/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gladiatorial_fight.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 17:20:05 by bdudley           #+#    #+#             */
/*   Updated: 2020/01/12 17:22:14 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "visual.h"

void		take_actions(t_info *info, t_processes *prs, t_sdl *sdl)
{
	if (prs->cc_op == 0)
	{
		if ((info->arena)[prs->index] > 0 && (info->arena)[prs->index] < 17)
		{
			prs->code_op = (info->arena)[prs->index];
			prs->cc_op = g_op_tab[prs->code_op - 1].cycle_for_exec;
		}
	}
	if (prs->cc_op > 0)
		--prs->cc_op;
	if (prs->cc_op == 0)
	{
		if ((info->arena)[prs->index] > 0 && (info->arena)[prs->index] < 17)
			g_op_tab[IND((info->arena)[prs->index])].func(info, &prs, sdl);
		else
		{
			if (sdl != NULL)
				move_cursor(prs->index, 1, -prs->reg[0] - 1, sdl);
			prs->index = (++(prs->index)) % MEM_SIZE;
		}
	}
}

void		kick_noobs(t_info *info, t_sdl *sdl)
{
	t_processes		*ptr;

	ptr = info->processes;
	while (ptr)
	{
		if (info->count_cycles - ptr->cc_live > info->cycle_to_die)
		{
			if (sdl != NULL)
			{
				update_byte(ptr->index, sdl);
				add_explosion(create_explosion(ptr->index), &sdl->head_explosion);
			}
			delete_elem(&ptr, info);
		}
		else
			ptr = ptr->next;
	}
	if (info->count_live >= NBR_LIVE || info->count_check < MAX_CHECKS)
	{
		info->count_check = -1;
		info->cycle_to_die -= CYCLE_DELTA;
	}
	++(info->count_check);
	info->i = -1;
	info->count_live = 0;
}

void		gladiatorial_fight(int *play, t_info *info, t_sdl *sdl)
{
	t_processes	*prs;

	while (info->processes)
	{
		while (++(info->i) <= info->cycle_to_die)
		{
			prs = info->processes;
			while (prs)
			{
				take_actions(info, prs, sdl);
				prs = prs->next;
			}
			++info->count_cycles;
			return ;
		}
		kick_noobs(info, sdl);
	}
	if (play != NULL)
		*play = -1;
}
