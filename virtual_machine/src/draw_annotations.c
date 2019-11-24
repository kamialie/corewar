/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_annotations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 16:35:59 by rgyles            #+#    #+#             */
/*   Updated: 2019/11/24 17:50:02 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visual.h"

void	show_players(t_sdl *sdl, t_info *info)
{
	int	i;
	int	num_players;
	char *text;
	t_render	render_info;
	SDL_Surface	*text_surface;
	//TMP PLAYERS
	char *players[4];
	players[0] = "kamil";
	players[1] = "vilena";
	players[2] = "katya";
	players[3] = "snova_kamil!";
	//

	render_info.rect.x = PLAYER_NAME_X_LOCATION;
	render_info.rect.y = PLAYER_Y_LOCATION;
	render_info.rect.w = 50; //make macros
	render_info.rect.h = 17; // make macros
	render_info.color = sdl->colors[WHITE];
	render_info.font = sdl->font;

	i = 0;
	num_players = 4;

	//text = PLAYER_ONE;
	while (i < num_players)
	{
		if (i == 0)
			text = PLAYER_ONE;
		else if (i == 1)
			text = PLAYER_TWO;
		else if (i == 2)
			text = PLAYER_THREE;
		else
			text = PLAYER_FOUR;

		render_info.rect.x = PLAYER_X_LOCATION;
		render_info.color = sdl->colors[WHITE];
		text_surface = TTF_RenderText_Blended(render_info.font, text, render_info.color);
		SDL_BlitSurface(text_surface, NULL, sdl->surface, &render_info.rect);
		SDL_FreeSurface(text_surface);

		render_info.rect.x = PLAYER_NAME_X_LOCATION;
		render_info.color = sdl->colors[i + 1];
		text_surface = TTF_RenderText_Blended(render_info.font, players[i], render_info.color);
		SDL_BlitSurface(text_surface, NULL, sdl->surface, &render_info.rect);
		SDL_FreeSurface(text_surface);

		render_info.rect.y += PLAYER_SECTION_HEIGHT;
		++i;
	}
		
	//i = 0;
	//while (i < num_players)
	//{
}




void	draw_annotations(t_sdl *sdl, t_info *info)
{
	show_players(sdl, info);
}
