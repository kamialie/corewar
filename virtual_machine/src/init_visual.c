/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_visual.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 14:40:04 by rgyles            #+#    #+#             */
/*   Updated: 2019/12/14 18:10:33 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visual.h"
#include "sound.h"

static void	init_colors(SDL_Color *colors)
{
	colors[BLACK] = (SDL_Color) {0, 0, 0};
	colors[WHITE] = (SDL_Color) {255, 255, 255};
	colors[YELLOW] = (SDL_Color) {255, 255, 0};
	colors[BLUE] = (SDL_Color) {0, 0, 255};
	colors[GREEN] = (SDL_Color) {0, 255, 0};
	colors[RED] = (SDL_Color) {255, 0, 0};
	colors[YELLOW_BACK] = (SDL_Color) {110, 110, 0};
	colors[BLUE_BACK] = (SDL_Color) {0, 0, 110};
	colors[GREEN_BACK] = (SDL_Color) {0, 110, 0};
	colors[RED_BACK] = (SDL_Color) {110, 0, 0};
}

static TTF_Font	*init_font(void) //need to add check
{
	TTF_Font	*font;

	TTF_Init(); //int sdl_ttf
	font = TTF_OpenFont(FONT_PATH, 15); //open font
	TTF_SetFontStyle(font, TTF_STYLE_BOLD);
	return (font);
}

void	init_music(t_sdl *sdl)
{
    int flags = MIX_INIT_MP3;

	if (flags != Mix_Init(flags)) // needs careful exit on error
	{
		//printf("Could not initialize mixer (result: %d).\n", result);
		printf("Mix_Init: %s\n", Mix_GetError());
		exit(1);
	}
    Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 640);
    sdl->main_theme = Mix_LoadMUS(MAIN_THEME); // check for null
	sdl->live_effect = Mix_LoadWAV(LIVE_EFFECT);
	if (sdl->live_effect == NULL)
	{
		printf("smth went wrong\n");
		exit(1);
	}
	Mix_VolumeChunk(sdl->live_effect, MIX_MAX_VOLUME);
}


/*
 * TODO remove printfs to putstr or smth
*/
int	init_sdl(t_sdl *sdl)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
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
	SDL_FreeSurface(sdl->surface);
	sdl->render_info = (t_render *)malloc(sizeof(t_render)); //check failure
	sdl->font = init_font(); // check for return status
	sdl->render_info->font = sdl->font; //interesting decision xD may be initialize to render info only?
	init_music(sdl); // needs work and getting error
	init_colors(sdl->colors);
	sdl->speed = 100; // default game speed
	sdl->img_data = (int *)sdl->surface->pixels; // do I need this?
	return (0);
}
