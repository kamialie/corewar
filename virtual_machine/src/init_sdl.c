/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sdl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 14:45:48 by rgyles            #+#    #+#             */
/*   Updated: 2020/01/18 17:24:56 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visual.h"
#include "sound.h"
#include "op.h"
#include "libft.h"

static void	init_colors(SDL_Color *colors)
{
	colors[BLACK] = (SDL_Color) {0, 0, 0};
	colors[WHITE] = (SDL_Color) {255, 255, 255};
	colors[YELLOW] = (SDL_Color) {255, 255, 0};
	colors[BLUE] = (SDL_Color) {0, 150, 255};
	colors[GREEN] = (SDL_Color) {0, 255, 0};
	colors[RED] = (SDL_Color) {255, 0, 0};
	colors[YELLOW_BACK] = (SDL_Color) {255, 150, 0};
	colors[BLUE_BACK] = (SDL_Color) {0, 150, 255};
	colors[GREEN_BACK] = (SDL_Color) {0, 150, 0};
	colors[RED_BACK] = (SDL_Color) {150, 0, 0};
}

/*
** TODO add check for null return
*/

static void	init_font(t_render *render_info)
{
	TTF_Init();
	render_info->font = TTF_OpenFont(FONT_PATH, 15);
	TTF_SetFontStyle(render_info->font, TTF_STYLE_BOLD);
}

void		init_music(t_sdl *sdl)
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
	Mix_VolumeMusic(50);
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
int	init_sdl(unsigned char *arena, t_sdl *sdl)
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
	sdl->head_explosion = NULL;
	SDL_FreeSurface(sdl->surface);
	sdl->render_info = (t_render *)malloc(sizeof(t_render)); //check failure
	init_font(sdl->render_info); // check for return status
	sdl->img_data = (int *)sdl->surface->pixels; // is needed for frame drawing
	sdl->replica = malloc(MEM_SIZE); //need to add check
	ft_bzero(sdl->replica, MEM_SIZE);
	init_music(sdl); // needs work and getting error
	init_colors(sdl->colors);
	sdl->arena = arena;
	return (0);
}
