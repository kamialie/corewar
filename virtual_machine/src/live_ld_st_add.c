/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live_ld_st_add.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 18:05:20 by bdudley           #+#    #+#             */
/*   Updated: 2019/12/14 17:00:40 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		live_op(t_info *info, t_processes **prs, t_sdl *sdl)
{
	int     arg;
	int     new_location;

    printf("live\n");
	(*prs)->cc_live = info->count_cycles;
	arg = (info->arena)[((*prs)->index + 1) % MEM_SIZE];
	if (arg == (*prs)->reg[0])
		info->last_live = (*prs)->reg[0];
	new_location = (((*prs)->index) + 5) % MEM_SIZE;
	create_cursor(info->arena[new_location], new_location, (*prs)->reg[0] - 1, sdl);
	update_byte(info->arena[(*prs)->index], (*prs)->index, (*prs)->reg[0] - 1, sdl);
	//move_cursor((*prs)->index, new_location, num_player - 1, sdl);
    (*prs)->index = new_location; //1 байт занимает код операции и 4 байта занимает аргумент
	//printf("cc_live %d\n./", (*prs)->cc_live);
}

void		ld_op(t_info *info, t_processes **prs, t_sdl *sdl)
{
    unsigned char code_arg;
    int           skiped_bytes;

    code_arg = ((info->arena)[((*prs)->index + 1) % MEM_SIZE]) & 0xf0;
    printf("%d   %d\n", code_arg, ((info->arena)[((*prs)->index + 1) % MEM_SIZE]));
    if (code_arg == 208)
    {
        skiped_bytes = 1;
    }
    else if (code_arg == 144)
    {
        skiped_bytes = 1;
    }
    else
       skiped_bytes = get_bytes_to_skip(1, code_arg);
    printf("skip %d\n", skiped_bytes);
    create_cursor(info->arena[((*prs)->index + skiped_bytes) % MEM_SIZE], ((*prs)->index + skiped_bytes) % MEM_SIZE, (*prs)->reg[0] - 1, sdl);
    update_byte(info->arena[(*prs)->index], (*prs)->index, (*prs)->reg[0] - 1, sdl);
    (*prs)->index = ((*prs)->index + skiped_bytes) % MEM_SIZE;
}

void		st_op(t_info *info, t_processes **prs, t_sdl *sdl)
{
//    create_cursor(info->arena[((*prs)->index + 1) % MEM_SIZE], ((*prs)->index + 1) % MEM_SIZE, (*prs)->reg[0] - 1, sdl);
//    update_byte(info->arena[(*prs)->index], (*prs)->index, (*prs)->reg[0] - 1, sdl);
//    (*prs)->index = (++((*prs)->index)) % MEM_SIZE;
}

void		add_op(t_info *info, t_processes **prs, t_sdl *sdl)
{
//    create_cursor(info->arena[((*prs)->index + 1) % MEM_SIZE], ((*prs)->index + 1) % MEM_SIZE, (*prs)->reg[0] - 1, sdl);
//    update_byte(info->arena[(*prs)->index], (*prs)->index, (*prs)->reg[0] - 1, sdl);
//    (*prs)->index = (++((*prs)->index)) % MEM_SIZE;
}
