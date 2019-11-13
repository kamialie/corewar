/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 18:17:31 by bdudley           #+#    #+#             */
/*   Updated: 2019/11/13 20:41:10 by bdudley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mach/mach_types.h>
#include "corewar.h"

void		delete_elem(t_processes **processes, t_info *info)
{
	t_processes		*copy;

	copy = (*processes);
	if ((*processes)->prev)
	{
		((*processes)->prev)->next = (*processes)->next;
		((*processes)->next)->prev = (*processes)->prev;
	}
	else if ((*processes)->next)
	{
		((*processes)->next)->prev = NULL;
		info->processes = (*processes)->next;
	}
	else
		info->processes = NULL;
	(*processes) = (*processes)->next;
	free(copy);
	copy = NULL;
}

void		add_elem(t_processes **processes, unsigned char	*ptr, int number_player)
{
	t_processes	*new;

	if (!(new = (t_processes *)malloc(sizeof(t_processes))))
		error(7); //Ошибка маллока
	new->next = NULL;
	new->prev = NULL;
	new->carry = 0;
	new->ptr = ptr;
	ft_bzero(new->reg, REG_NUMBER * REG_SIZE);
	(new->reg)[REG_SIZE - 4] += (number_player & 0xff);
	(new->reg)[REG_SIZE - 3] += (number_player & 0xff00);
	(new->reg)[REG_SIZE - 2] += (number_player & 0xff0000);
	(new->reg)[REG_SIZE - 1] += (number_player & 0xff000000);
	if (*processes == NULL)
		*processes = new;
	else
	{
		new->next = *processes;
		(*processes)->prev = new;
		*processes = new;
	}
}

void		create_processes(t_info *info)
{
	int 	i;
	int 	shift;

	i = 0;
	while (++i <= info->count_process)
	{
		shift = (MEM_SIZE / info->count_process) * (i - 1);
		add_elem(&(info->processes), info->arena + shift, i);
	}
}