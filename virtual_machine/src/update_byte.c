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

void		set_render_color(int type, int player, t_render *render_info, SDL_Color *colors)
{
	if (type == EMPTY)
	{
		render_info->font_color = colors[WHITE];
		render_info->back_color = colors[BLACK];
	}
	else if (type == CURSOR)
	{
		render_info->font_color = colors[WHITE];
		render_info->back_color = colors[player + BACK_COLOR];
	}
	else
	{
		render_info->font_color = colors[player + FONT_COLOR];
		render_info->back_color = colors[BLACK];
	}
}

void		set_render_location(int location, t_render *render_info)
{
	render_info->rect.x = NIBBLE_X_SHIFT + NIBBLE_WIDTH * (location % 64);
	render_info->rect.y = NIBBLE_Y_SHIFT + NIBBLE_HEIGHT * (location / 64);
}

t_render	create_render_info(TTF_Font *font)
{
	t_render	render_info;
	
	render_info.font = font;
	render_info.rect.w = NIBBLE_WIDTH;
	render_info.rect.h = NIBBLE_HEIGHT;
	return (render_info);
}

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
