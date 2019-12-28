/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 15:50:24 by rgyles            #+#    #+#             */
/*   Updated: 2019/12/28 16:23:26 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visual.h"
#include "corewar.h"

void	event_handler(t_info *info, t_sdl *sdl)
{
	int	key;
	int	play;
	int	show;
	int	seed;
	SDL_Event event;

	play = 0;
	show = 0;
	seed = 0;
    //Mix_PlayMusic(sdl->main_theme, 1); // commented for no music while debugging
	while (1)
	{
		if (play)
		{
			printf("count_cycles %d\n", info->count_cycles);

			show_data(info, sdl);

            gladiatorial_fight(info, sdl);

			SDL_UpdateWindowSurface(sdl->window); //draw surface
			SDL_Delay(sdl->speed);
		}
		if (show)
		{
			update_arena(seed++, sdl);
			SDL_UpdateWindowSurface(sdl->window); //draw surface
			SDL_Delay(sdl->speed);
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
				else if (key == SDLK_SPACE)
				{
					play = play == 0 ? 1 : 0;
					update_game_status(play, sdl);
				}
				else if (key == SDLK_EQUALS && sdl->speed > 0)
				{
					printf("increase\n");
					sdl->speed -= 50;
					show_sdl_data(sdl);
					SDL_UpdateWindowSurface(sdl->window); //draw surface
				}
				else if (key == SDLK_MINUS && sdl->speed < 1000)
				{
					printf("decrease\n");
					sdl->speed += 50;
					show_sdl_data(sdl);
					SDL_UpdateWindowSurface(sdl->window); //draw surface
				}
				else if (key == SDLK_n)
				{
					printf("count_cycles %d\n", info->count_cycles);
					show_data(info, sdl);
					gladiatorial_fight(info, sdl);
					SDL_UpdateWindowSurface(sdl->window); //draw surface
				}
				else if (key == SDLK_p)
				{
					printf("music on/off\n");
					if (Mix_PausedMusic())
						Mix_ResumeMusic();
					else
						Mix_PauseMusic();
				}
				else if (key == SDLK_s)
					Mix_FadeOutMusic(3000);
				else if (key == SDLK_l)
					Mix_PlayChannel(-1, sdl->live_effect, 0);
				else if (key == SDLK_a)
					show = show == 0 ? 1 : 0;
			}
		}
	}
}
