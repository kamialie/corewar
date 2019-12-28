/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_text.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 20:02:31 by rgyles            #+#    #+#             */
/*   Updated: 2019/12/28 20:09:30 by rgyles           ###   ########.fr       */
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
