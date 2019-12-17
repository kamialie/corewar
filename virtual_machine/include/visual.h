/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 16:09:49 by rgyles            #+#    #+#             */
/*   Updated: 2019/12/14 18:30:49 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISUAL_H
# define VISUAL_H

# include "SDL.h"
# include "SDL_ttf.h"
# include "sdl_struct.h"

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

# define GAME_STATUS_X_LOCATION 1400
# define GAME_STATUS_Y_LOCATION 30

# define PLAYER_ONE "Player 1: "
# define PLAYER_TWO "Player 2: "
# define PLAYER_THREE "Player 3: "
# define PLAYER_FOUR "Player 4: "

# define PLAYER_X_LOCATION 1380
# define PLAYER_Y_LOCATION 200
# define PLAYER_NAME_X_LOCATION 1400
# define PLAYER_NAME_Y_LOCATION 140
# define PLAYER_SECTION_HEIGHT 102

# define INFO_X_LOCATION 1420
# define INFO_Y_LOCATION 50

# define INFO_Y_SHIFT 20

# define DATA_X_LOCATION 1570
# define DATA_Y_LOCATION 50

# define SDL_DATA_X_LOCATION 1570
# define SDL_DATA_Y_LOCATION 150

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
void			set_nibble_for_render(int location, int type, int player, t_sdl *sdl);
void			set_render_color(int type, int player, t_render *render_info, SDL_Color *colors);
void			draw_byte(unsigned char byte, t_render *render_info, SDL_Surface *surface);
void			show_sdl_data(t_sdl *sdl);

void			draw_square(t_square sq_info, int *img_data);

void			update_game_status(int status, t_sdl *sdl);

#endif
