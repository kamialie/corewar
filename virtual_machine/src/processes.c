/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 18:17:31 by bdudley           #+#    #+#             */
/*   Updated: 2019/11/12 20:54:19 by bdudley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

//void		put_reguster(int number)
//{
//	int 	i;
//
//	i = 0;
//	while (i < REG_SIZE)
//	{
//
//	}
//}

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
	if (*processes == NULL)
		*processes = new;
	else
	{
		new->next = *processes;
		(*processes)->prev = new;
		*processes = new;
	}
}

void		create_processes(t_info info)
{
	int 	i;
	int 	shift;

	i = 0;
	while (++i <= info.count_process)
	{
		shift = (MEM_SIZE / info.count_process) * (i - 1);
		add_elem(&(info.processes), info.arena + shift, i);
	}
}