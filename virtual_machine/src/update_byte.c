/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_byte.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 15:31:27 by rgyles            #+#    #+#             */
/*   Updated: 2019/11/30 16:57:48 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visual.h"

void	update_byte(int location, int player, t_sdl *sdl)
{
	t_render	render_info;

	render_info = create_render_info(sdl->font);
	set_render_location(location, &render_info);
	set_render_color(CODE, player, &render_info, sdl->colors);
	draw_byte(location, &render_info, sdl->surface);
}

void	create_cursor(int location, int player, t_sdl *sdl)
{
	t_render	render_info;

	render_info = create_render_info(sdl->font);
	set_render_location(location, &render_info);
	set_render_color(CURSOR, player, &render_info, sdl->colors);
	draw_byte(location, &render_info, sdl->surface);
}

void	move_cursor(int cur_location, int new_location, int player, t_sdl *sdl)
{
	create_cursor(new_location, player, sdl);
	update_byte(cur_location, player, sdl);
}
