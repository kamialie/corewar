/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_visual_arena.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 17:20:29 by rgyles            #+#    #+#             */
/*   Updated: 2019/11/30 17:00:16 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SDL_ttf.h"
#include "visual.h"
#include "libft.h"

/*SDL_Color	choose_color(int i)
{
	int	limits[8];

	ft_bzero(limits, 8 * 4);
	limits[1] = 100;
	
	if (num_of_players >= 1)
	{
		if (i >= 0 && i <= limits[1])
			return ((SDL_Color) {255, 255, 0});
		if (num_of_players >= 2)
		{
			if (i >= limits[2] && i <= limits[3]) 
				return ((SDL_Color) {0, 0, 255});
			if (num_of_players >= 3)
			{
		}
	}
	return ((SDL_Color) {255, 255, 255});
}*/

/*void	draw_arena_grid(t_sdl *sdl, unsigned char *arena)
{

	int i;
	int w;
	int h;
	int count;

	i = 1;
	w = 21;
	h = 17;
	count = 65;
	while (i < count)
	{
		draw_vertical_line(i * w, sdl->surface->h - 11, 0xFF, sdl->img_data);
		++i;
	}
	i = 1;
	count = 65;
	while (i < count)
	{
		draw_horizontal_line(i * h, sdl->surface->w - 455, 0xFF, sdl->img_data);
		++i;
	}
}*/


/*
 * former function to output one row
*/
/*void	draw_arena_row(unsigned char *arena, int row, t_render *info, t_sdl *sdl)
{
	int	i;
	int	last;

	last = (row + 1) * 64;
	i = last - 64;
	//draw_byte(arena[i], info, sdl);
	draw_byte(i, info, sdl);
	while (++i < last)
	{
		printf("i - %d\n", i);
		info->rect.x += NIBBLE_WIDTH;
		draw_byte(i, info, sdl);
		//draw_byte(arena[i++], info, sdl);
	}
}*/

/*
 * former function to output arena without coloring
 * currently outputs just current number, change i in draw_byte to draw actual data
*/
/*void	draw_arena(unsigned char *arena, t_render render_info, SDL_Surface *surface)
{
	int	i;
	int i_last;
	int	row;
	int	row_last;

	row = 0;
	row_last = 64;
	while (row < row_last)
	{
		i_last = (row + 1) * 64;
		i = i_last - 64;
		render_info.rect.x = NIBBLE_X_SHIFT;
		//render_info.color = choose_color(i);
		draw_byte(i, &render_info, surface);
		while (++i < i_last)
		{
			render_info.rect.x += NIBBLE_WIDTH;
			//render_info.color = choose_color(i);
			draw_byte(i, &render_info, surface);
		}
		render_info.rect.y += NIBBLE_HEIGHT;
		++row;
	}
}*/

/*
 * draw range from i to end
 * end_of_row detects last index(one dimenstion) on the current row(two dimension)
*/
void	draw_range(int i, int end, unsigned char *arena, t_render *render_info, SDL_Surface *surface)
{
	int end_of_row;
	int	row;

	row = i / 64;
	end_of_row = (row + 1) * 64;
	while (1)
	{
		while (i < end_of_row)
		{
			if (i == end)
				return ;
			draw_byte(arena[i++], render_info, surface);
			render_info->rect.x += NIBBLE_WIDTH;
		}
		render_info->rect.y += NIBBLE_HEIGHT;
		render_info->rect.x = NIBBLE_X_SHIFT;
		end_of_row = (++row + 1) * 64;
		i = end_of_row - 64;
	}
}

void	initialize_visual_arena(t_sdl *sdl, t_info *info)
{
	t_render	render_info;

	// draw memory edges
	t_square	sq_info;

	sq_info = (t_square) {0, WIN_HEIGHT - 1, WIN_WIDTH - 445, 0, 0xFFA500};
   	draw_square(sq_info, sdl->img_data);
	//end

	//draw_arena_grid(sdl, arena);
	
	int	range[9];
	range[0] = 0;
	range[1] = 150;
	//range[2] = 4096;
	range[2] = 500;
	range[3] = 1000;
	//range[4] = 4096;
	range[4] = 2300;
	range[5] = 2500;
	//range[6] = 4096;
	range[6] = 3000;
	range[7] = 3500;
	range[8] = 4096;

	int	i;
	int	player = 0;
	int	num_players = 4;
	int end;

	render_info = create_render_info(sdl->font);
	while (player < num_players)
	{
		i = range[player * 2];
		end = player * 2 + 1;

		set_render_location(i, &render_info);
		set_render_color(CURSOR, player, &render_info, sdl->colors);
		draw_byte(i, &render_info, sdl->surface);

		set_render_location(i + 1, &render_info);
		set_render_color(CODE, player, &render_info, sdl->colors);
		draw_range(i + 1, range[end], info->arena, &render_info, sdl->surface);

		set_render_location(range[end], &render_info);
		set_render_color(EMPTY, player, &render_info, sdl->colors);
		draw_range(range[end], range[end + 1], info->arena, &render_info, sdl->surface);
		++player;
	}

	draw_annotations(sdl, info); // draw side menu, info

	move_cursor(0, 3, 0, sdl);

	create_cursor(15, 0, sdl);

	SDL_UpdateWindowSurface(sdl->window); //draw surface

	event_handler(sdl); // loop

	TTF_CloseFont(sdl->font); //free memory used by font
	SDL_DestroyWindow(sdl->window);
	TTF_Quit();
	SDL_Quit();
}

/*
 * Render example
	SDL_Renderer* renderer = SDL_CreateRenderer(sdl->window, -1, SDL_RENDERER_ACCELERATED);
	SDL_RenderClear(renderer);

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, message);
	SDL_QueryTexture(texture, NULL, NULL, &tw, &th); // get info of the texture, can directrly access surface attributes - width and height
	SDL_RenderCopy(renderer, texture, NULL, &dsrect);
	
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderDrawLine(renderer, 0, 0, 50, 50);
	SDL_RenderDrawLine(renderer, 300, 240, 340, 240);
	SDL_RenderDrawLine(renderer, 340, 240, 320, 200);
	
	SDL_RenderPresent(renderer);
	SDL_FreeSurface(sdl->surface);
*/
