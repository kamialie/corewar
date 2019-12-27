/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_byte.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 15:31:27 by rgyles            #+#    #+#             */
/*   Updated: 2019/12/14 16:42:10 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visual.h"
#include "op.h"

void	set_byte(int location, int player, t_sdl *sdl)
{
	sdl->replica[location] = player + 1;
}

/*void	update_byte(unsigned char value, int location, int player, t_sdl *sdl) // need to remove player integer - taken from replica
{
	set_nibble_for_render(location, CODE, sdl->replica[location], sdl);
	draw_byte(value, sdl->render_info, sdl->surface);
}*/

void	update_byte(int location, t_sdl *sdl) // need to remove player integer - taken from replica
{
	set_nibble_for_render(location, CODE, sdl->replica[location], sdl);
	draw_byte(sdl->arena[location], sdl->render_info, sdl->surface);
}

/*
 * player comes from processes info.
 * where player number start from 0
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
