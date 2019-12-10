/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_annotations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 16:35:59 by rgyles            #+#    #+#             */
/*   Updated: 2019/11/30 15:09:07 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		get_size(int number)
{
	int	size;
	
	size = 0;
	if (number < 0)
	{
		number *= -1;
		size++;
	}
	while (number > 0)
	{
		number /= 10;
		size++;
	}
	return (size);
}

void	int_to_char(int number, char *str)
{
	int		index;

	if (number == 0)
	{
		str[0] = '0';
		str[1] = '\0';
	}
	else
	{
		index = get_size(number);
		str[index] = '\0';
		if (number < 0)
		{
			number *= -1;
			str[0] = '-';
		}
		while (number > 0)
		{
			str[--index] = (number % 10) + '0';
			number /= 10;
		}
	}
}

void	render_text(char *text, t_render *render_info, SDL_Surface *surface)
{
	SDL_Surface	*text_surface;

	text_surface = TTF_RenderText_Shaded(render_info->font, text, (SDL_Color) {255, 255, 255}, (SDL_Color) {0, 0, 0});
	SDL_BlitSurface(text_surface, NULL, surface, &render_info->rect);
	SDL_FreeSurface(text_surface);
}

void	show_cycle(t_info *info, t_sdl *sdl)
{
	char	buffer[30];
	t_render	render_info;

	render_info.rect.x = CYCLE_X_LOCATION;
	render_info.rect.y = CYCLE_Y_LOCATION;
	render_info.rect.w = 50; //make macros
	render_info.rect.h = 17; // make macros
	render_info.font_color = sdl->colors[WHITE];
	render_info.font_color = sdl->colors[BLACK];
	render_info.font = sdl->font;
	int_to_char(info->count_cycles, buffer);
	render_text(buffer, &render_info, sdl->surface);
}

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
	render_info.font_color = sdl->colors[WHITE];
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
		render_info.font_color = sdl->colors[WHITE];
		render_text(text, &render_info, sdl->surface);

		render_info.rect.x = PLAYER_NAME_X_LOCATION;
		render_info.font_color = sdl->colors[i + 1];
		render_text(players[i], &render_info, sdl->surface);

		render_info.rect.y += PLAYER_SECTION_HEIGHT;
		++i;
	}


		
	//i = 0;
	//while (i < num_players)
	//{
}

void	draw_annotations(t_sdl *sdl, t_info *info)
{
	t_render render_info;

	render_info.rect.x = CYCLE_X_LOCATION - 80;
	render_info.rect.y = CYCLE_Y_LOCATION;
	render_info.rect.w = 50; //make macros
	render_info.rect.h = 17; // make macros
	render_info.font_color = sdl->colors[WHITE];
	render_info.font = sdl->font;
	render_text("cycle - ", &render_info, sdl->surface);
	show_cycle(info, sdl);

	show_players(sdl, info);
}
