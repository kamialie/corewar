/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 16:09:49 by rgyles            #+#    #+#             */
/*   Updated: 2019/11/17 17:18:27 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISUAL_H
# define VISUAL_H

# include "SDL.h"
# include "SDL_ttf.h"

# define WIN_HEIGHT 1100
# define WIN_WIDTH 1800

typedef struct	s_sdl
{
	SDL_Window	*window;
	SDL_Surface	*surface;
	int			*img_data;
}				t_sdl;

typedef struct	s_render
{
	SDL_Rect	rect;
	TTF_Font	*font;
	SDL_Color	*color;
}				t_render;


void	draw(t_sdl *sdl, unsigned char *arena);
void	event_handler(t_sdl *sdl);

#endif
