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

	text_surface = TTF_RenderText_Shaded(render_info->font, text, render_info->font_color, render_info->back_color);
	SDL_BlitSurface(text_surface, NULL, surface, &render_info->rect);
	SDL_FreeSurface(text_surface);
}

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

void	show_data(int data, int shift, t_sdl *sdl)
{
	char	buffer[30];
	t_render	render_info;

	render_info.rect.x = CYCLE_X_LOCATION;
	if (shift >= 500)
		render_info.rect.x += 70;
	render_info.rect.y = CYCLE_Y_LOCATION + shift;
	render_info.rect.w = 50; //make macros
	render_info.rect.h = 17; // make macros
	render_info.font_color = sdl->colors[WHITE];
	render_info.back_color = sdl->colors[BLACK];
	render_info.font = sdl->font;
	int_to_char(data, buffer);
	render_text(buffer, &render_info, sdl->surface);
}

void	update_game_status(int status, t_sdl *sdl)
{
	sdl->render_info->rect.x = GAME_STATUS_X_LOCATION;
	sdl->render_info->rect.y = GAME_STATUS_Y_LOCATION;
	sdl->render_info->rect.w = 65; //make macros
	sdl->render_info->rect.y = 17; //make macros
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

	sdl->render_info->rect.x = CYCLE_X_LOCATION - 80;
	sdl->render_info->rect.y = CYCLE_Y_LOCATION;
	sdl->render_info->rect.w = 50; //make macros
	sdl->render_info->rect.h = 17; // make macros
	sdl->render_info->font_color = sdl->colors[WHITE];
	sdl->render_info->back_color = sdl->colors[BLACK];

	render_text("cycle - ", sdl->render_info, sdl->surface);
	sdl->render_info->rect.y = CYCLE_Y_LOCATION + 500;
	render_text("last_live - ", sdl->render_info, sdl->surface);
	sdl->render_info->rect.y = CYCLE_Y_LOCATION + 520;
	render_text("cycle to die - ", sdl->render_info, sdl->surface);
	sdl->render_info->rect.y = CYCLE_Y_LOCATION + 540;
	render_text("count_live - ", sdl->render_info, sdl->surface);
	sdl->render_info->rect.y = CYCLE_Y_LOCATION + 560;
	render_text("count_check - ", sdl->render_info, sdl->surface);

	show_data(info->count_cycles, 0, sdl);
	show_data(info->last_live, 500, sdl);
	show_data(info->cycle_to_die, 520, sdl);
	show_data(info->count_live, 540, sdl);
	show_data(info->count_check, 560, sdl);

	update_game_status(0, sdl);

	show_players(info, sdl);
}
