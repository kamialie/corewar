/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 13:34:54 by rgyles            #+#    #+#             */
/*   Updated: 2019/11/13 16:11:19 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visual.h"
#include "corewar.h"

void 	init_info(t_info *info)
{
	int		i;

	info->arena = (unsigned char *)malloc(MEM_SIZE); //check NULL
	ft_bzero(info->arena, MEM_SIZE);
	info->dump = -1;
	i = -1;
	while (++i < MAX_PLAYERS)
	{
		(info->players)[i].magic = 0;
		(info->players)[i].prog_size = 0;
		ft_bzero((info->players)[i].prog_name, PROG_NAME_LENGTH + 1);
		ft_bzero((info->players)[i].comment, COMMENT_LENGTH + 1);
	}
}

static int	init_sdl(t_sdl *sdl)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		printf("SDL_Init Error: %s\n", SDL_GetError());
		return (1);
	}
	sdl->win = SDL_CreateWindow("Corewar",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,1024,500,SDL_WINDOW_SHOWN);
	if (sdl->win == NULL)
	{
		printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
		return (1);
	}
	sdl->surface = SDL_GetWindowSurface(sdl->win);
	if (sdl->surface == NULL)
	{
		printf("SDL_GetWindowSurface Error: %s\n", SDL_GetError());
		return (1);
	}
	SDL_FillRect(sdl->surface, NULL, SDL_MapRGB( sdl->surface->format, 0x0, 0x0, 0x0));
	//sdl.img_data = (int *)sdl.surface->pixels;
	SDL_UpdateWindowSurface(sdl->win);
	return (0);
}

int	main(int argc , char *argv[])
{
	t_info		info;
	t_sdl		sdl;

	init_info(&info);
	read_arg(&info, argc, argv);
	//print_arena(info.arena);
	if (init_sdl(&sdl))
		return (1);
	event_handler(&sdl);
	SDL_Quit();
	return (0);
}
