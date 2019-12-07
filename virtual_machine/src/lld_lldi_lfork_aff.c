/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lld_lldi_lfork_aff.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 18:10:13 by bdudley           #+#    #+#             */
/*   Updated: 2019/11/17 19:27:17 by bdudley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		lld_op(t_info *info, t_processes **prs, t_sdl *sdl)
{

}

void		lldi_op(t_info *info, t_processes **prs, t_sdl *sdl)
{

}

void		lfork_op(t_info *info, t_processes **prs, t_sdl *sdl)
{
    int     i;

	printf("lfork\n");
	add_elem(&(info->processes), *((int *)(info->arena + ((*prs)->index + 1) % MEM_SIZE)) + (*prs)->index, ((*prs)->reg)[0]);
	(info->processes)->carry = (*prs)->carry;
	(info->processes)->cc_live = (*prs)->cc_live;
    i = -1;
    while (++i < REG_NUMBER)
        (info->processes)->reg[i] = (*prs)->reg[i];
	(*prs)->index = (((*prs)->index) + 3) % MEM_SIZE; //1 байт занимает код операции и 2 байта занимает аргумент
}

void		aff_op(t_info *info, t_processes **prs, t_sdl *sdl)
{

}