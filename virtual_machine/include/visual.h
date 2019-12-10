/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 16:09:49 by rgyles            #+#    #+#             */
/*   Updated: 2019/11/30 16:59:04 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISUAL_H
# define VISUAL_H

# include "SDL.h"
# include "SDL_ttf.h"

# define FONT_PATH "sdl/fonts/FreeMono.ttf"
# define WIN_HEIGHT 1160
# define WIN_WIDTH 1800

# define NIBBLE_X_SHIFT 7
# define NIBBLE_Y_SHIFT 5

# define NIBBLE_WIDTH 21
# define NIBBLE_HEIGHT 18

# define BLACK 0
# define WHITE 1
# define YELLOW 2
# define BLUE 3
# define GREEN 4
# define RED 5
# define YELLOW_BACK 6
# define BLUE_BACK 7
# define GREEN_BACK 8
# define RED_BACK 9

# define FONT_COLOR 2
# define BACK_COLOR 6

# define EMPTY 0
# define CURSOR 1
# define CODE 2

# define PLAYER_ONE "Player 1: "
# define PLAYER_TWO "Player 2: "
# define PLAYER_THREE "Player 3: "
# define PLAYER_FOUR "Player 4: "

# define PLAYER_X_LOCATION 1360
# define PLAYER_Y_LOCATION 120
# define PLAYER_NAME_X_LOCATION 1445
# define PLAYER_SECTION_HEIGHT 102

# define CYCLE_X_LOCATION 1500
# define CYCLE_Y_LOCATION 50

typedef struct	s_sdl
{
	SDL_Window	*window;
	SDL_Surface	*surface;
	int			*img_data;
	SDL_Color	colors[9];
	TTF_Font	*font;
}				t_sdl;

typedef struct	s_render
{
	SDL_Rect	rect;
	SDL_Color	font_color;
	SDL_Color	back_color;
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

int				init_sdl(t_sdl *sdl);
void			draw_byte(unsigned char byte, t_render *render_info, SDL_Surface *surface);
void			set_render_color(int type, int player, t_render *render_info, SDL_Color *colors);
void			set_render_location(int location, t_render *render_info);
t_render		create_render_info(TTF_Font *font);
void			draw_square(t_square sq_info, int *img_data);
void			set_render_color(int type, int player, t_render *render_info, SDL_Color *colors);
void			set_render_location(int location, t_render *render_info);
t_render		create_render_info(TTF_Font *font);
void			draw_byte(unsigned char byte, t_render *render_info, SDL_Surface *surface);
void			update_byte(int location, int player, t_sdl *sdl);
void			move_cursor(int cur_location, int new_location, int player, t_sdl *sdl);
void			create_cursor(int location, int player, t_sdl *sdl);


#endif
