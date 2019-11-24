/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_visual.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 14:40:04 by rgyles            #+#    #+#             */
/*   Updated: 2019/11/24 15:34:43 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visual.h"
#include "libft.h"

static void	init_colors(SDL_Color *colors)
{
	colors[WHITE] = (SDL_Color) {255, 255, 255};
	colors[YELLOW] = (SDL_Color) {255, 255, 0};
	colors[GREEN] = (SDL_Color) {0, 0, 255};
	colors[BLUE] = (SDL_Color) {0, 255, 0};
	colors[RED] = (SDL_Color) {255, 0, 0};
}

static TTF_Font	*init_font(void)
{
	TTF_Font	*font;

	TTF_Init(); //int sdl_ttf
	font = TTF_OpenFont(FONT_PATH, 15); //open font
	return (font);
}

/*
 * TODO remove printfs to putstr or smth
*/
int	init_sdl(t_sdl *sdl)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		printf("SDL_Init Error: %s\n", SDL_GetError());
		return (1);
	}
	sdl->window = SDL_CreateWindow("Corewar", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
	if (sdl->window == NULL)
	{
		printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
		return (1);
	}
	sdl->surface = SDL_GetWindowSurface(sdl->window);
	if (sdl->surface == NULL)
	{
		printf("SDL_GetWindowSurface Error: %s\n", SDL_GetError());
		return (1);
	}
	init_colors(sdl->colors);
	sdl->font = init_font(); // check for return status
	sdl->img_data = (int *)sdl->surface->pixels;
	ft_bzero(sdl->img_data, WIN_WIDTH * WIN_HEIGHT * 4);
	return (0);
}
