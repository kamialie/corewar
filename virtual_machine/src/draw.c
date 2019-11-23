/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 16:25:36 by rgyles            #+#    #+#             */
/*   Updated: 2019/11/23 21:01:04 by rgyles           ###   ########.fr       */
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
 * nibble is 4 bits!
*/
char	get_nibble(unsigned char nibble)
{
	//printf("number - %d\n", (int)nibble);
	if (nibble < 10)
		return (48 + nibble);
	else if (nibble == 10)
		return ('a');
	else if (nibble == 11)
		return ('b');
	else if (nibble == 12)
		return ('c');
	else if (nibble == 13)
		return ('d');
	else if (nibble == 14)
		return ('e');
	else
		return ('f');
}

/*
** render single byte:
** divide byte into nibbles, get the corresponding base 16 symbols, form a string
** render text using TTF, set coordinates, copy to window surface, free orginal surface created by TTF
*/
void	draw_byte(unsigned char byte, t_render *info, SDL_Surface *surface)
{
	char cell[3];
	SDL_Surface	*text_surface;

	cell[0] = get_nibble((byte & 0xf0) >> 4);
	cell[1] = get_nibble(byte & 0xf);
	cell[2] = '\0';
	text_surface = TTF_RenderText_Blended(info->font, cell, info->color);
	SDL_BlitSurface(text_surface, NULL, surface, &info->rect);
	SDL_FreeSurface(text_surface);
}

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

void	draw_arena(unsigned char *arena, t_render render_info, SDL_Surface *surface)
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
}

void	draw_range(unsigned char *arena, t_render *render_info, SDL_Surface *surface, int i, int end)
{
	int i_last;
	int	row;

	row = i / 64;
	i_last = (row + 1) * 64;
	render_info->rect.x = NIBBLE_X_SHIFT + NIBBLE_WIDTH * (i % 64);
	render_info->rect.y = NIBBLE_Y_SHIFT + NIBBLE_HEIGHT * (i / 64);
	while (1)
	{
		//render_info.color = choose_color(i);
		//draw_byte(i, render_info, surface);
		while (i < i_last)
		{
			printf("i - %d\n", i);
			if (i == end)
				return ;
			draw_byte(i, render_info, surface);
			render_info->rect.x += NIBBLE_WIDTH;
			//render_info.color = choose_color(i);
			++i;
		}
		render_info->rect.y += NIBBLE_HEIGHT;
		render_info->rect.x = NIBBLE_X_SHIFT;
		++row;
		i_last = (row + 1) * 64;
		i = i_last - 64;
	}
}

void	draw(t_sdl *sdl, unsigned char *arena)
{
	int	tw;
	int th;
	t_render	info;

	TTF_Init(); //int sdl_ttf
	TTF_Font* font = TTF_OpenFont("sdl/fonts/OpenSans-Regular.ttf", 15); //open font
	SDL_Color white = {255, 255, 255}; //set color
	SDL_Color red = {255, 0, 0}; //set color

	//SDL_Rect rect = {NIBBLE_X_SHIFT, NIBBLE_Y_SHIFT, 21, 17};
	//info.rect = rect;
	info.color = white;
	info.font = font;
	info.rect.x = NIBBLE_X_SHIFT;
	info.rect.y = NIBBLE_Y_SHIFT;
	info.rect.w = NIBBLE_WIDTH;
	info.rect.h = NIBBLE_HEIGHT;

	// draw memory edges
	t_square	sq_info;

	sq_info = (t_square) {0, WIN_HEIGHT - 1, WIN_WIDTH - 452, 0, 0xFFA500};
   	draw_square(sq_info, sdl->img_data);
	//end

	//draw_arena_grid(sdl, arena);
	
	//draw_arena_row(arena, 0, &info, sdl);

	//draw_arena(arena, info, sdl->surface);

	//draw_range(arena, &info, sdl->surface, 65, 128);
	SDL_Color colors[5];
	colors[0] = (SDL_Color) {255, 255, 0};
	colors[1] = (SDL_Color) {0, 0, 255};
	colors[2] = (SDL_Color) {0, 255, 0};
	colors[3] = (SDL_Color) {255, 0, 0};
	colors[4] = (SDL_Color) {255, 255, 255};

	int	range[9];
	range[0] = 0;
	range[1] = 150;
	range[2] = 1000;
	range[3] = 2000;
	range[4] = 3096;
	range[5] = 3500;
	range[6] = 4096;

	int	i = 1;
	int	num_players = 2;
	info.color = colors[0];
	draw_range(arena, &info, sdl->surface, 0, range[1]);
	info.color = colors[4];
	draw_range(arena, &info, sdl->surface, range[1], range[2]);
	while (i < num_players)
	{
		info.color = colors[i];
		draw_range(arena, &info, sdl->surface, range[i * 2], range[i * 2 + 1]);
		info.color = colors[4];
		draw_range(arena, &info, sdl->surface, range[i * 2 + 1], range[i * 2 + 2]);
		i++;
	}


	SDL_UpdateWindowSurface(sdl->window); //draw surface

	event_handler(sdl); // loop

	TTF_CloseFont(font); //free memory used by font
	SDL_DestroyWindow(sdl->window);
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
