/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_visual_arena.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 17:20:29 by rgyles            #+#    #+#             */
/*   Updated: 2020/01/12 14:55:36 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visual.h"
#include "corewar.h"

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

void	draw_memory_frame(t_sdl *sdl)
{
	t_square	sq_info;

	sq_info = (t_square) {0, WIN_HEIGHT - 1, WIN_WIDTH - 445, 0, 0xFFA500};
   	draw_square(&sq_info, sdl->img_data);
	sq_info = (t_square) {WIN_WIDTH - 444, WIN_HEIGHT - 500, WIN_WIDTH - 1, 0, 0x33CCFF};
   	draw_square(&sq_info, sdl->img_data);
	sq_info = (t_square) {WIN_WIDTH - 444, WIN_HEIGHT - 1, WIN_WIDTH - 1, WIN_HEIGHT - 500, 0x6600CC};
   	draw_square(&sq_info, sdl->img_data);
}

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
 * increment start, as cursor will be initialized in another function
 */
void	draw_arena(t_processes *processes, t_info *info, t_sdl *sdl)
{
	int	start;
	int end;
	int	player;

	player = 1;
	while (processes != NULL)
	{
		start = processes->index; //cursor will be initialized later, in anther function
		end = start + ((info->players)[player - 1]).prog_size;
		++start;
		set_nibble_for_render(start, CODE, player, sdl);
		draw_range(start, end, info->arena, sdl);
		set_nibble_for_render(end, EMPTY, player, sdl);
		if (processes->prev == NULL)
			draw_range(end, MEM_SIZE, info->arena, sdl);
		else
			draw_range(end, (processes->prev)->index, info->arena, sdl);
		++player;
		processes = processes->prev;
	}
}

void	draw_cursors(t_processes *processes, t_info *info, t_sdl *sdl)
{
	int	index;

	while (processes != NULL)
	{
		index = processes->index;
		printf("after - %d\n", sdl->replica[processes->index]);
		//printf("value - %d\n", sdl->replica[index + 1]);
		set_nibble_for_render(index, CURSOR, sdl->replica[index], sdl);
		draw_byte(info->arena[index], sdl->render_info, sdl->surface);
		processes = processes->prev;
	}
}

/*
 * set duplicating array to represent which codes belongs to which player
*/
void	set_replica(t_processes *processes, t_info *info, t_sdl *sdl)
{
	int	i;
	int end;
	int	player;
	unsigned char	*replica;

	player = 1;
	replica = sdl->replica;
	while (processes != NULL)
	{
		i = processes->index;
		//printf("index is - %d value is - %d\n", i, player);
		end = i + ((info->players)[player - 1]).prog_size;
		while (i < end)
		{
			replica[i] = player;
			++i;
		}
		printf("before - %d\n", replica[processes->index]);
		++player;
		processes = processes->prev;
	}
}

/*
 * while loop to go back to first plater
*/
void	initialize_visual_arena(t_sdl *sdl, t_info *info)
{

	draw_memory_frame(sdl); //draw frame for memory
	
	t_processes	*processes = info->processes;
	while (processes->next != NULL)
		processes = processes->next;
	set_replica(processes, info, sdl);
	/*int k = 0;
	for (int j = 0; j < 64; j++) {
		for (int i = 0; i < 64; i++) {
			printf("%d ", sdl->replica[k++]);
		}
		printf("\n");
	}*/
	draw_cursors(processes, info, sdl);
	draw_arena(processes, info, sdl);
	
	draw_annotations(info, sdl); // draw side menu, info
	draw_game_controls(sdl);

	//move_cursor(0, 3, 0, sdl); //for testing 

	//create_cursor(15, 0, sdl); //for testing 
	/*update_arena(sdl);
	for (int i = 0; i < 64; i++) {
		for (int j = 0; j < 64; j++) {
			//printf("%d", j + 64 * i);
			printf("%d ", sdl->replica[j + 64 * i]);
		}
		printf("\n");
	}*/

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
