/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 16:25:36 by rgyles            #+#    #+#             */
/*   Updated: 2019/11/16 20:45:37 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SDL_ttf.h"
#include "visual.h"
#include "libft.h"

void	draw_vertical_line(int x, int h, int *img_data)
{
	int	y;

	y = 0;
	while (y < h)
	{
		img_data[y * WIN_WIDTH + x] = 0xFF;
		++y;
	}
}

void	draw_horizontal_line(int y, int w, int	*img_data)
{
	int	x;

	x = 0;
	while (x < w)
	{
		img_data[y * WIN_WIDTH + x] = 0xFF;
		++x;
	}
}

void	draw_arena_grid(t_sdl *sdl, unsigned char *arena)
{

	int i;
	int a;
	int count;

	i = 1;
	a = 30;
	count = 33;
	while (i < count)
	{
		draw_vertical_line(i * a, sdl->surface->h, sdl->img_data);
		++i;
	}
	i = 1;
	count = 33;
	while (i < count)
	{
		draw_horizontal_line(i * a, sdl->surface->w, sdl->img_data);
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
	printf("number - %d\n", (int)nibble);
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

void	print_byte(unsigned char byte, int x, int y, TTF_Font *font, SDL_Color color, t_sdl *sdl)
{
	char cell[3];
	SDL_Surface	*text_surface;
	SDL_Rect rect;

	printf("byte - %d\n", byte);
	//printf("nibble_one - %d\n", ((byte & 0xf0) >> 4));
	cell[0] = print_nibble((byte & 0xf0) >> 4);
	cell[1] = print_nibble(byte & 0xf);
	cell[2] = '\0';
	text_surface = TTF_RenderText_Solid(font, cell, color);
	rect = (SDL_Rect) {0, 0, x, y};
	SDL_BlitSurface(text_surface, NULL, sdl->surface, &rect);
}

/*void	output_arena_row(unsigned char *arena, int row, t_sdl *sdl)
{
	int	i;
	int	row;

	total = (row + 1) * 32;
	i = total - 32;
}*/

void	draw(t_sdl *sdl, unsigned char *arena)
{
	int	tw;
	int th;

	TTF_Init(); //int sdl_ttf
	TTF_Font* font = TTF_OpenFont("sdl/fonts/OpenSans-Regular.ttf", 22); //open font
	SDL_Color white = {255, 255, 255}; //set color

	SDL_Surface* message = TTF_RenderText_Solid(font, "some text", white); // render text
	SDL_Rect dsrect = {0, 0, tw, th}; //set square where to draw the message
	//SDL_BlitSurface(message, NULL, sdl->surface, &dsrect); // copy from message to the surface
	//printf("w - %d h - %d\n", message->w, message->h);

	message = TTF_RenderText_Solid(font, "8a", white);
	dsrect = (SDL_Rect) {30, 30, tw, th};
	SDL_BlitSurface(message, NULL, sdl->surface, &dsrect);

	printf("tw - %d th - %d\n", tw, th);

	draw_arena_grid(sdl, arena);

	//void	print_byte(int byte, int x, int y, TTF_Font *font, SDL_Color color, t_sdl *sdl)
	print_byte(0xf0, 30, 30, font, white, sdl);

	SDL_UpdateWindowSurface(sdl->window); //draw surface

	event_handler(sdl); // loop

	SDL_DestroyWindow(sdl->window);
	TTF_CloseFont(font); //free memory used by font
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
