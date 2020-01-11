/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project_sdl.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 16:17:50 by rgyles            #+#    #+#             */
/*   Updated: 2020/01/11 17:53:55 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROJECT_SDL
# define PROJECT_SDL

# include "SDL.h"
# include "SDL_ttf.h"
# include "SDL_mixer.h"

typedef struct	s_render
{
	SDL_Rect	rect;
	SDL_Color	font_color;
	SDL_Color	back_color;
	TTF_Font	*font;
}				t_render;

typedef struct	s_sdl
{
	int				*img_data;
	unsigned char	*arena;
	unsigned char	*replica;
	SDL_Window		*window;
	SDL_Surface		*surface;
	SDL_Color		colors[9];
	Mix_Music		*main_theme;
	Mix_Chunk		*live_effect;
	t_render		*render_info;
}				t_sdl;

#endif
