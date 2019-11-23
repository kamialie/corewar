/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 16:09:49 by rgyles            #+#    #+#             */
/*   Updated: 2019/11/23 16:32:54 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISUAL_H
# define VISUAL_H

# include "SDL.h"
# include "SDL_ttf.h"

# define WIN_HEIGHT 1100
# define WIN_WIDTH 1800

# define NIBBLE_X_SHIFT 5
# define NIBBLE_Y_SHIFT 3

# define NIBBLE_WIDTH 21
# define NIBBLE_HEIGHT 17

typedef struct	s_sdl
{
	SDL_Window	*window;
	SDL_Surface	*surface;
	int			*img_data;
}				t_sdl;

typedef struct	s_render
{
	SDL_Rect	rect;
	SDL_Color	color;
	TTF_Font	*font;
}				t_render;

/*
 * x0, y0 - lower left corner
 * x1, y1 - top right corner
*/
typedef struct	s_square
{
	int	x0;
	int	y0;
	int	x1;
	int y1;
	int	color;
}				t_square;

void	draw(t_sdl *sdl, unsigned char *arena);
void	draw_square(t_square sq_info, int *img_data);
void	event_handler(t_sdl *sdl);

#endif
