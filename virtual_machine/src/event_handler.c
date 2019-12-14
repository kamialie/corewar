/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 15:50:24 by rgyles            #+#    #+#             */
/*   Updated: 2019/12/14 17:58:25 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visual.h"
#include "corewar.h"

void	event_handler(t_info *info, t_sdl *sdl)
{
	int	key;
	int	play;
	SDL_Event event;

	play = 0;
	while (1)
	{
		if (play)
		{
			printf("count_cycles %d\n", info->count_cycles);

			show_data(info, sdl);

            gladiatorial_fight(info, sdl);

			SDL_UpdateWindowSurface(sdl->window); //draw surface
			SDL_Delay(100);
		}
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				return ;
			SDL_PumpEvents();
			if (event.type == SDL_KEYDOWN)
			{
				key = event.key.keysym.sym;
				if (key == SDLK_ESCAPE)
					return ;
				if (key == SDLK_SPACE)
				{
					play = play == 0 ? 1 : 0;
					update_game_status(play, sdl);
				}
			}
		}
	}
}
