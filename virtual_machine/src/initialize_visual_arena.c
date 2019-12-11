/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_visual_arena.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 17:20:29 by rgyles            #+#    #+#             */
/*   Updated: 2019/12/07 16:42:31 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

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
void	draw_range(int i, int end, unsigned char *arena, t_sdl *sdl)
{
	int			end_of_row;
	int			row;
	t_render	*render_info;
	SDL_Surface	*surface;

	render_info = sdl->render_info;
	surface = sdl->surface;
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

/*
 * trying to write range initialization
 *
*/
/*void	prepare_range_array(int *range, t_info *info)
{
	int	i;
	int	end;
	int	shift;
	int	size;

	i = 0;
	end = 1;
	size = (info->players)[i].prog_size;
	while (size != 0)
	{
		shift = (MEM_SIZE / count) * i;
		range[i] = shift;
		range[end] = range[i] + size;
	}
}*/

void	draw_memory_frame(t_sdl *sdl)
{
	t_square	sq_info;

	sq_info = (t_square) {0, WIN_HEIGHT - 1, WIN_WIDTH - 445, 0, 0xFFA500};
   	draw_square(sq_info, sdl->img_data);
	//draw_arena_grid(sdl, arena);
}

void	draw_arena(t_processes *processes, t_info *info, t_sdl *sdl)
{
	int	start;
	int end;
	int	player;

	player = 0;
	while (processes != NULL)
	{
		start = processes->index;
		end = start + ((info->players)[player]).prog_size;
		set_nibble_for_render(start, CURSOR, player, sdl);
		draw_byte(start, sdl->render_info, sdl->surface);
		set_nibble_for_render(start + 1, CODE, player, sdl);
		draw_range(start + 1, end, info->arena, sdl);
		set_nibble_for_render(end, EMPTY, player, sdl);
		if (processes->prev == NULL)
			draw_range(end, MEM_SIZE, info->arena, sdl);
		else
			draw_range(end, (processes->prev)->index, info->arena, sdl);
		player++;
		processes = processes->prev;
	}
}


void	initialize_visual_arena(t_sdl *sdl, t_info *info)
{

	draw_memory_frame(sdl); //draw frame for memory
	
	sdl->render_info->rect.w = NIBBLE_WIDTH;
	sdl->render_info->rect.h = NIBBLE_HEIGHT;
	t_processes	*processes = info->processes;
	while (processes->next != NULL)
		processes = processes->next;
	draw_arena(processes, info, sdl);
	
	draw_annotations(sdl, info); // draw side menu, info

	move_cursor(0, 3, 0, sdl);

	create_cursor(15, 0, sdl);

	SDL_UpdateWindowSurface(sdl->window); //draw surface
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
