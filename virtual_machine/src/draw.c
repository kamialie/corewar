/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 16:25:36 by rgyles            #+#    #+#             */
/*   Updated: 2019/11/16 19:33:36 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visual.h"
#include "SDL_ttf.h"
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

void	draw_arena_grid(t_sdl *sdl)
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

void	draw(t_sdl *sdl)
{
	TTF_Init(); //int sdl_ttf
	TTF_Font* font = TTF_OpenFont("sdl/fonts/OpenSans-Regular.ttf", 24); //open font
	SDL_Color white = {255, 255, 255}; //set color
	SDL_Surface* message = TTF_RenderText_Solid(font, "some text", white); // render text

	printf("w - %d h - %d\n", message->w, message->h);

	int	tw;
	int th;
	SDL_Rect dsrect = {0, 0, tw, th};
	SDL_BlitSurface(message, NULL, sdl->surface, &dsrect);
	printf("tw - %d th - %d\n", tw, th);

	draw_arena_grid(sdl);

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
