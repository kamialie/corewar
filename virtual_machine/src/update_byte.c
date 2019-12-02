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

t_render	set_render_info(int location, TTF_Font *font)
{
	t_render	render_info;
	
	render_info.font = font;
	render_info.rect.w = NIBBLE_WIDTH;
	render_info.rect.h = NIBBLE_HEIGHT;
	render_info.rect.x = NIBBLE_X_SHIFT + NIBBLE_WIDTH * (location % 64);
	render_info.rect.y = NIBBLE_Y_SHIFT + NIBBLE_HEIGHT * (location / 64);
	return (render_info);
}

void	update_byte(int location, int player, int is_cursor, t_sdl *sdl)
{
	t_render	render_info;

	render_info.rect.x = NIBBLE_X_SHIFT + NIBBLE_WIDTH * (location % 64);
	render_info.rect.y = NIBBLE_Y_SHIFT + NIBBLE_HEIGHT * (location / 64);
	if (is_cursor)
		render_info.back_color = sdl->colors[player + 6];
	else
		render_info.font_color = sdl->colors[player + 2];
	draw_byte(location, &render_info, sdl->surface);
	SDL_UpdateWindowSurface(sdl->window); //draw surface
}

void	move_cursor(int cur_location, int new_location, int player, t_sdl *sdl)
{
	t_render	render_info;

	render_info.font = sdl->font;
	render_info.rect.w = NIBBLE_WIDTH;
	render_info.rect.h = NIBBLE_HEIGHT;
	render_info.cursor = 0;
	render_info.font_color = sdl->colors[player + 2];
	render_info.rect.x = NIBBLE_X_SHIFT + NIBBLE_WIDTH * (cur_location % 64);
	render_info.rect.y = NIBBLE_Y_SHIFT + NIBBLE_HEIGHT * (cur_location / 64);
	draw_byte(cur_location, &render_info, sdl->surface);

	render_info.cursor = 1;
	render_info.back_color = sdl->colors[player + 6];
	render_info.rect.x = NIBBLE_X_SHIFT + NIBBLE_WIDTH * (new_location % 64);
	render_info.rect.y = NIBBLE_Y_SHIFT + NIBBLE_HEIGHT * (new_location / 64);
	draw_byte(new_location, &render_info, sdl->surface);
	SDL_UpdateWindowSurface(sdl->window); //draw surface
}

void	create_cursor(int location, int player, t_sdl *sdl)
{
	t_render	render_info;

	render_info = set_render_info(location, sdl->font);
	render_info.font_color = sdl->colors[WHITE];
	render_info.back_color = sdl->colors[player + 6];
	draw_byte(location, &render_info, sdl->surface);
	SDL_UpdateWindowSurface(sdl->window); //draw surface
}
