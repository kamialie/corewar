/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_text.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 20:02:31 by rgyles            #+#    #+#             */
/*   Updated: 2020/01/11 17:19:56 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visual.h"

void	render_text(char *text, t_render *render_info, SDL_Surface *surface)
{
	SDL_Surface	*text_surface;

	text_surface = TTF_RenderText_Shaded(render_info->font, text, render_info->font_color, render_info->back_color);
	SDL_BlitSurface(text_surface, NULL, surface, &render_info->rect);
	SDL_FreeSurface(text_surface);
}

void	render_text_outline(char *text, t_render *render_info, SDL_Surface *surface) // for winner announcement
{
	SDL_Surface	*text_surface;

	text_surface = TTF_RenderText_Shaded(render_info->font, text, render_info->font_color, render_info->back_color);
	SDL_BlitSurface(text_surface, NULL, surface, &render_info->rect);
	SDL_FreeSurface(text_surface);
}
