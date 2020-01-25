/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 15:50:24 by rgyles            #+#    #+#             */
/*   Updated: 2020/01/25 14:59:04 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visual.h"
#include "corewar.h"

static void	music_controls(int key, t_controls *controls, t_sdl *sdl)
{
	if (key == SDLK_p)
	{
		if (Mix_PausedMusic())
			Mix_ResumeMusic();
		else
			Mix_PauseMusic();
	}
	else if (key == SDLK_s)
		Mix_FadeOutMusic(3000);
	else if (key == SDLK_l)
		Mix_PlayChannel(-1, sdl->live_effect, 0);
	else if (key == SDLK_b)
		Mix_PlayChannel(-1, sdl->birth_effect, 0);
}

static void	game_controls(int key, t_controls *controls,
								t_info *info, t_sdl *sdl)
{
	if (key == SDLK_SPACE)
	{
		controls->play = controls->play == 0 ? 1 : 0;
		update_game_status(controls->play, sdl);
	}
	else if (key == SDLK_n)
	{
		gladiatorial_fight(&controls->play, info, sdl);
		show_data(info, sdl);
		SDL_UpdateWindowSurface(sdl->window);
	}
	else if (key == SDLK_i && controls->speed > 0)
	{
		controls->speed -= 50;
		udpate_delay(controls->speed, sdl);
		SDL_UpdateWindowSurface(sdl->window);
	}
	else if (key == SDLK_d && controls->speed < 1000)
	{
		controls->speed += 50;
		udpate_delay(controls->speed, sdl);
		SDL_UpdateWindowSurface(sdl->window);
	}
	else if (key == SDLK_a) //temporary
		controls->play = -1;
	else if (key == SDLK_e) //temporary
		add_explosion(create_explosion(224), &sdl->head_explosion); // Vilena vzriv
	else
		music_controls(key, controls, sdl);
}

static void	take_game_action(t_controls *controls, t_info *info, t_sdl *sdl)
{
	if (controls->play == GAME_RUNNING)
	{
		gladiatorial_fight(&controls->play, info, sdl);
		show_data(info, sdl);
	}
	else if (controls->play == GAME_SHOW && sdl->head_explosion == NULL)
	{
		if (controls->show_time-- > 0)
		{
			controls->speed = 150;
			epilepsy(controls->seed++, sdl->render_info, sdl->surface, sdl);
		}
		else
		{
			announce_winner(info->last_live, info, sdl);
			controls->play = GAME_OVER;
		}
	}
	if (controls->play != GAME_PAUSED || sdl->head_explosion)
	{
		draw_explosion(sdl->head_explosion, sdl);
		SDL_UpdateWindowSurface(sdl->window);
		SDL_Delay(controls->speed);
	}
}

void		event_handler(t_info *info, t_sdl *sdl)
{
	int			key;
	SDL_Event	event;
	t_controls	controls;

	controls = (t_controls) {GAME_PAUSED, DEFAULT_GAME_SPEED, 20, 0};
	//Mix_PlayMusic(sdl->main_theme, 1); // commented for no music while debugging
	while (1)
	{
		if (controls.play != GAME_OVER)
			take_game_action(&controls, info, sdl);
		if (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				return ;
			SDL_PumpEvents();
			if (event.type == SDL_KEYDOWN)
			{
				key = event.key.keysym.sym;
				if (key == SDLK_ESCAPE)
					return ;
				else if (controls.play >= GAME_PAUSED)
					game_controls(key, &controls, info, sdl);
			}
		}
	}
}
