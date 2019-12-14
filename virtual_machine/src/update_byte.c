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

void	update_byte(unsigned char value, int location, int player, t_sdl *sdl)
{
	set_nibble_for_render(location, CODE, player, sdl);
	draw_byte(value, sdl->render_info, sdl->surface);
}

void	create_cursor(unsigned char value, int location, int player, t_sdl *sdl)
{
	set_nibble_for_render(location, CURSOR, player, sdl);
	draw_byte(value, sdl->render_info, sdl->surface);
}

/*hvoid	move_cursor(int cur_location, int new_location, int player, t_sdl *sdl)
{
	create_cursor(new_location, player, sdl);
	update_byte(cur_location, player, sdl);
}*/
