/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 16:25:36 by rgyles            #+#    #+#             */
/*   Updated: 2019/11/14 18:32:41 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visual.h"
#include "SDL_ttf.h"
#include "libft.h"

void	draw(t_sdl *sdl)
{
	TTF_Init();
	TTF_Font* sans = TTF_OpenFont("OpenSans-Regular.ttf", 24);
	SDL_Color white = {255, 255, 255};
	SDL_Surface* message = TTF_RenderText_Solid(sans, "some text", white);

	printf("w - %d h - %d\n", message->w, message->h);
	//printf("w - %d h - %d\n", sdl->surface->w, sdl->surface->h);

	/*int y;
	int x;
	char	*src;
	char	*dst;
	src = (char *)message->pixels;
	dst = (char *)sdl->surface->pixels;

	y = 0;
	while (y < message->h)
	{
		x = 0;
		while (x < message->w)
		{
			dst[x + y * sdl->surface->w] = src[x + y * message->w];
			x++;
		}
		y++;
	}*/

	SDL_Renderer* renderer = SDL_CreateRenderer(sdl->window, -1, SDL_RENDERER_ACCELERATED);
	SDL_RenderClear(renderer);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, message);
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderDrawLine(renderer, 0, 0, 50, 50);
	SDL_RenderDrawLine(renderer, 300, 240, 340, 240);
	SDL_RenderDrawLine(renderer, 340, 240, 320, 200);

	SDL_RenderPresent(renderer);

	//ft_memcpy(sdl->img_data, message->pixels, message->w * message->pitch);
	//SDL_UpdateWindowSurface(sdl->window);
	event_handler(sdl);
	//SDL_FreeSurface(sdl->surface);
	SDL_DestroyWindow(sdl->window);
	SDL_Quit();
}
