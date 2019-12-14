/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_annotations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 16:35:59 by rgyles            #+#    #+#             */
/*   Updated: 2019/12/14 18:38:57 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visual.h"
#include "corewar.h"

void	show_players(t_info *info, t_sdl *sdl)
{
	int	i;
	char *text;

	//sdl->render_info->rect.w = 50; //make macros
	//sdl->render_info->rect.h = 17; // make macros
	sdl->render_info->rect.y = PLAYER_Y_LOCATION;
	sdl->render_info->back_color = sdl->colors[BLACK];

	i = 0;
	while (i < info->count_process)
	{
		if (i == 0)
			text = PLAYER_ONE;
		else if (i == 1)
			text = PLAYER_TWO;
		else if (i == 2)
			text = PLAYER_THREE;
		else
			text = PLAYER_FOUR;

		sdl->render_info->rect.x = PLAYER_X_LOCATION;
		sdl->render_info->font_color = sdl->colors[WHITE];
		render_text(text, sdl->render_info, sdl->surface);
		sdl->render_info->rect.y += 20;

		sdl->render_info->rect.x = PLAYER_NAME_X_LOCATION;
		sdl->render_info->font_color = sdl->colors[i + 2];
		render_text(info->players[i].prog_name, sdl->render_info, sdl->surface);

		sdl->render_info->rect.y += PLAYER_SECTION_HEIGHT;
		++i;
	}
}

void	update_game_status(int status, t_sdl *sdl)
{
	sdl->render_info->rect.x = GAME_STATUS_X_LOCATION;
	sdl->render_info->rect.y = GAME_STATUS_Y_LOCATION;
	sdl->render_info->rect.w = 65; //make macros
	sdl->render_info->rect.h = 20; //make macros
	if (status == 1)
	{
		sdl->render_info->font_color = sdl->colors[GREEN];
		render_text("RUNNING", sdl->render_info, sdl->surface);
	}
	else
	{
		sdl->render_info->font_color = sdl->colors[RED];
		SDL_FillRect(sdl->surface, &sdl->render_info->rect, 0);
		render_text("PAUSED", sdl->render_info, sdl->surface);
		SDL_UpdateWindowSurface(sdl->window); //draw surface
	}
}

void	draw_annotations(t_info *info, t_sdl *sdl)
{
	t_render render_info;

	sdl->render_info->font_color = sdl->colors[WHITE];
	sdl->render_info->back_color = sdl->colors[BLACK];
	sdl->render_info->rect.x = INFO_X_LOCATION;
	sdl->render_info->rect.y = INFO_Y_LOCATION;

	render_text("cycle - ", sdl->render_info, sdl->surface);
	sdl->render_info->rect.y += INFO_Y_SHIFT;
	render_text("last_live - ", sdl->render_info, sdl->surface);
	sdl->render_info->rect.y += INFO_Y_SHIFT;
	render_text("cycle to die - ", sdl->render_info, sdl->surface);
	sdl->render_info->rect.y += INFO_Y_SHIFT;
	render_text("count_live - ", sdl->render_info, sdl->surface);
	sdl->render_info->rect.y += INFO_Y_SHIFT;
	render_text("count_check - ", sdl->render_info, sdl->surface);
	sdl->render_info->rect.y += INFO_Y_SHIFT;
	render_text("speed - ", sdl->render_info, sdl->surface);

	show_data(info, sdl);
	show_sdl_data(sdl);

	update_game_status(0, sdl);

	show_players(info, sdl);
}
