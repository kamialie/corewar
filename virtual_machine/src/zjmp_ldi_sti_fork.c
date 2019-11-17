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

void		zjmp_op(t_info *info, t_processes **prs)
{
	printf("zjmp\n");
	if ((*prs)->carry)
	{
		(*prs)->index = (*prs)->index + *((int *)(info->arena + (*prs)->index + 1)) % IDX_MOD;
	}
	(*prs)->index = (((*prs)->index) + 3) % MEM_SIZE; //1 байт занимает код операции и 2 байта занимает аргумент
}

void		ldi_op(t_info *info, t_processes **prs)
{

}

void		sti_op(t_info *info, t_processes **prs)
{

}

void		fork_op(t_info *info, t_processes **prs)
{
	short	int 	*ptr;

	//ptr = (short int *)(1365 + 1 + info->arena);
	//printf("%d\n", ((*prs)->index));
	printf("fork %d\n", 0);
	add_elem(&(info->processes), *((int *)(info->arena + ((*prs)->index + 1) % MEM_SIZE)) % IDX_MOD, ((*prs)->reg)[0]);
	info->processes->carry = (*prs)->carry;
	(info->processes)->cc_live = (*prs)->cc_live;
	ft_strcpy((info->processes)->reg + REG_SIZE, (*prs)->reg + REG_SIZE);
	(*prs)->index = (((*prs)->index) + 3) % MEM_SIZE; //1 байт занимает код операции и 2 байта занимает аргумент
}
