/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 17:49:29 by rgyles            #+#    #+#             */
/*   Updated: 2020/01/11 19:02:11 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visual.h"
#include "corewar.h"

void	update_value(int data, t_render *render_info, SDL_Surface *surface)
{
	char	buffer[30];

	int_to_char(data, buffer);
	render_text(buffer, render_info, surface);
}

void	udpate_speed(int speed, t_sdl *sdl)
{
	t_render *render_info;

	render_info = sdl->render_info;
	render_info->rect.x = SDL_DATA_X_LOCATION;
	render_info->rect.y = SDL_DATA_Y_LOCATION;
	render_info->font_color = sdl->colors[WHITE];
	render_info->back_color = sdl->colors[BLACK];
	SDL_FillRect(sdl->surface, &sdl->render_info->rect, 0);
	if (speed == 0)
		render_text("no delay", render_info, sdl->surface);
	else
		update_value(speed, render_info, sdl->surface);
}

void	show_data(t_info *info, t_sdl *sdl)
{
	t_render *render_info;

	render_info = sdl->render_info;
	render_info->rect.x = DATA_X_LOCATION;
	render_info->rect.y = DATA_Y_LOCATION;
	render_info->font_color = sdl->colors[WHITE];
	render_info->back_color = sdl->colors[BLACK];
	update_value(info->count_cycles, render_info, sdl->surface);
	sdl->render_info->rect.y += TEXT_Y_SHIFT;
	update_value(info->last_live, render_info, sdl->surface);
	sdl->render_info->rect.y += TEXT_Y_SHIFT;
	update_value(info->cycle_to_die, render_info, sdl->surface);
	sdl->render_info->rect.y += TEXT_Y_SHIFT;
	update_value(info->count_live, render_info, sdl->surface);
	sdl->render_info->rect.y += TEXT_Y_SHIFT;
	update_value(info->count_check, render_info, sdl->surface);
}
