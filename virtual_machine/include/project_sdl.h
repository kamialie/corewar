/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project_sdl.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 16:17:50 by rgyles            #+#    #+#             */
/*   Updated: 2019/12/14 18:09:49 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROJECT_SDL
# define PROJECT_SDL

# include "SDL.h"
# include "SDL_ttf.h"

typedef struct	s_render
{
	SDL_Rect	rect;
	SDL_Color	font_color;
	SDL_Color	back_color;
	TTF_Font	*font;
}				t_render;

typedef struct	s_sdl
{
	int			speed;
	SDL_Window	*window;
	SDL_Surface	*surface;
	int			*img_data;
	SDL_Color	colors[9];
	TTF_Font	*font;
	t_render	*render_info;
}				t_sdl;

#endif
