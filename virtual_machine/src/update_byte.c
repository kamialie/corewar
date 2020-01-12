/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_byte_c.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 15:46:42 by rgyles            #+#    #+#             */
/*   Updated: 2020/01/12 15:47:48 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visual.h"
#include "op.h"

void	set_byte(int location, int player, t_sdl *sdl)
{
	sdl->replica[location] = player + 1;
}

void	update_byte(int location, t_sdl *sdl)
{
	set_nibble_for_render(location, CODE, sdl->replica[location], sdl);
	draw_byte(sdl->arena[location], sdl->render_info, sdl->surface);
}

/*
** player comes from processes info.
** where player number start from 0
*/

void	create_cursor(int location, int player, t_sdl *sdl)
{
	set_nibble_for_render(location, CURSOR, player + 1, sdl);
	draw_byte(sdl->arena[location], sdl->render_info, sdl->surface);
}

void	move_cursor(int location, int shift, int player, t_sdl *sdl)
{
	create_cursor((location + shift) % MEM_SIZE, player, sdl);
	update_byte(location, sdl);
}
