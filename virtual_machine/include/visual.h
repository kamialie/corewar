/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 16:09:49 by rgyles            #+#    #+#             */
/*   Updated: 2019/11/24 18:44:09 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISUAL_H
# define VISUAL_H

# include "SDL.h"
# include "SDL_ttf.h"
//TMP
# include "corewar.h"
//

# define FONT_PATH "sdl/fonts/OpenSans-Regular.ttf"
# define WIN_HEIGHT 1100
# define WIN_WIDTH 1800

# define NIBBLE_X_SHIFT 5
# define NIBBLE_Y_SHIFT 3

# define NIBBLE_WIDTH 21
# define NIBBLE_HEIGHT 17

# define WHITE 0
# define YELLOW 1
# define BLUE 2
# define GREEN 3
# define RED 4

# define PLAYER_ONE "Player 1: "
# define PLAYER_TWO "Player 2: "
# define PLAYER_THREE "Player 3: "
# define PLAYER_FOUR "Player 4: "

# define PLAYER_X_LOCATION 1360
# define PLAYER_Y_LOCATION 120
# define PLAYER_NAME_X_LOCATION 1445
# define PLAYER_SECTION_HEIGHT 102

typedef struct	s_sdl
{
	SDL_Window	*window;
	SDL_Surface	*surface;
	int			*img_data;
	SDL_Color	colors[8];
	TTF_Font	*font;
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

int		init_sdl(t_sdl *sdl);
void	initialize_visual_arena(t_sdl *sdl, t_info *info);
void	draw_square(t_square sq_info, int *img_data);
void	draw_annotations(t_sdl *sdl, t_info *info);
void	event_handler(t_sdl *sdl);

#endif
