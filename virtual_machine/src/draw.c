/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 16:25:36 by rgyles            #+#    #+#             */
/*   Updated: 2019/11/17 19:18:10 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SDL_ttf.h"
#include "visual.h"
#include "libft.h"

void	draw_vertical_line(int x, int h, int color, int *img_data)
{
	int	y;

	y = 0;
	while (y < h)
	{
		img_data[y * WIN_WIDTH + x] = color;
		++y;
	}
}

void	draw_horizontal_line(int y, int w, int color, int	*img_data)
{
	int	x;

	x = 0;
	while (x < w)
	{
		img_data[y * WIN_WIDTH + x] = color;
		++x;
	}
}

void	draw_arena_grid(t_sdl *sdl, unsigned char *arena)
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
}

/*void	print_arena_row(unsigned char *arena, int row)
{
	int i;
	int	total;

	total = (row + 1) * 32;
	i = total - 32;
	print_bit((arena[i] & 0xf) >> 4);
	print_bit(arena[i] & 0xf);
	while (i++ < total)
	{
		ft_putchar(' ');
		print_bit((arena[i] & 0xf0) >> 4);
		print_bit(arena[i] & 0xf);
	}
}*/

char	print_nibble(unsigned char nibble) // nibble is 4 bits!
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
void	draw_byte(unsigned char byte, t_render *info, t_sdl *sdl)
{
	char cell[3];
	SDL_Surface	*text_surface;
	//SDL_Rect rect;

	//printf("byte - %d\n", byte);
	cell[0] = print_nibble((byte & 0xf0) >> 4);
	cell[1] = print_nibble(byte & 0xf);
	cell[2] = '\0';
	text_surface = TTF_RenderText_Solid(info->font, cell, info->color);
	SDL_BlitSurface(text_surface, NULL, sdl->surface, &info->rect);
	SDL_FreeSurface(text_surface);
}

void	draw_arena_row(unsigned char *arena, int row, t_render *info, t_sdl *sdl)
{
	int	i;
	int	last;

	last = (row + 1) * 64;
	i = last - 64;
	info->rect.x = 5;
	info->rect.y = 0;
	info->rect.w = 21;
	info->rect.h = 17;
	draw_byte(arena[i], info, sdl);
	while (i++ < last)
	{
		info->rect.x += NIBBLE_WIDTH;
		draw_byte(arena[i], info, sdl);
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

	SDL_Rect rect = {0 + NIBBLE_X_SHIFT, 0 - NIBBLE_Y_SHIFT, 21, 17};
	info.rect = rect;
	info.color = white;
	info.font = font;

	//SDL_Surface* message = TTF_RenderText_Solid(font, "some text", white); // render text
	//SDL_Rect dsrect = {0, 0, tw, th}; //set square where to draw the message

	//message = TTF_RenderText_Solid(font, "8a", white);
	//dsrect = (SDL_Rect) {30, 30, tw, th};
	//SDL_BlitSurface(message, NULL, sdl->surface, &dsrect);

	printf("tw - %d th - %d\n", tw, th);

	// draw memory edges
	draw_vertical_line(0, WIN_HEIGHT, 0xFFA500, sdl->img_data);
	draw_vertical_line(1, WIN_HEIGHT, 0xFFA500, sdl->img_data);
	draw_vertical_line(1344, WIN_HEIGHT, 0xFFA500, sdl->img_data);
	draw_vertical_line(1345, WIN_HEIGHT, 0xFFA500, sdl->img_data);
	draw_horizontal_line(0, WIN_WIDTH - 455, 0xFFA500, sdl->img_data);
	draw_horizontal_line(1, WIN_WIDTH - 455, 0xFFA500, sdl->img_data);
	draw_horizontal_line(WIN_HEIGHT - 1, WIN_WIDTH - 455, 0xFFA500, sdl->img_data);
	draw_horizontal_line(WIN_HEIGHT - 2, WIN_WIDTH - 455, 0xFFA500, sdl->img_data);
	// end

	draw_arena_grid(sdl, arena);

	//void	print_byte(int byte, int x, int y, TTF_Font *font, SDL_Color color, t_sdl *sdl)
	//draw_byte(0xf0, &info, sdl);
	draw_arena_row(arena, 0, &info, sdl);

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
