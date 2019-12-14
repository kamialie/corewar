/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 17:49:29 by rgyles            #+#    #+#             */
/*   Updated: 2019/12/14 18:53:09 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visual.h"
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

void	update_value(int data, t_render *render_info, SDL_Surface *surface)
{
	char	buffer[30];

	int_to_char(data, buffer);
	render_text(buffer, render_info, surface);
}

void	show_sdl_data(t_sdl *sdl)
{
	t_render *render_info;

	render_info = sdl->render_info;
	render_info->rect.x = SDL_DATA_X_LOCATION;
	render_info->rect.y = SDL_DATA_Y_LOCATION;
	render_info->rect.w = 90;
	render_info->rect.h = 20;
	render_info->font_color = sdl->colors[WHITE];
	render_info->back_color = sdl->colors[BLACK];
	SDL_FillRect(sdl->surface, &sdl->render_info->rect, 0);
	if (sdl->speed == 0)
		render_text("no delay", render_info, sdl->surface);
	else
		update_value(sdl->speed, render_info, sdl->surface);
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
	sdl->render_info->rect.y += INFO_Y_SHIFT;
	update_value(info->last_live, render_info, sdl->surface);
	sdl->render_info->rect.y += INFO_Y_SHIFT;
	update_value(info->cycle_to_die, render_info, sdl->surface);
	sdl->render_info->rect.y += INFO_Y_SHIFT;
	update_value(info->count_live, render_info, sdl->surface);
	sdl->render_info->rect.y += INFO_Y_SHIFT;
	update_value(info->count_check, render_info, sdl->surface);
}
