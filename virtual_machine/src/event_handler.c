/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 15:50:24 by rgyles            #+#    #+#             */
/*   Updated: 2019/12/07 16:11:28 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visual.h"
#include "corewar.h"
//TMP
#include <time.h>
//END

void	event_handler(t_info *info, t_sdl *sdl)
{
	int	key;
	int	play;
	SDL_Event event;
	//TMP
	struct timespec req = {0, 500000000};
	//END

	play = 1;
	while (1)
	{
		if (play)
		{
			nanosleep(&req, NULL);
			printf("count_cycles %d\n", info->count_cycles);
			show_cycle(info, sdl);
			SDL_UpdateWindowSurface(sdl->window); //draw surface
			gladiatorial_fight(info, sdl);
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
					play = play == 0 ? 1 : 0;
			}
		}
	}
}
