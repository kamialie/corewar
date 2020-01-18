/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 15:50:24 by rgyles            #+#    #+#             */
/*   Updated: 2020/01/18 13:41:06 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visual.h"
#include "corewar.h"

static void	update_for_one_round(int delay, int *play, t_info *info, t_sdl *sdl)
{
	printf("count_cycles %d\n", info->count_cycles);
	show_data(info, sdl);
	gladiatorial_fight(play, info, sdl);
	SDL_UpdateWindowSurface(sdl->window);
	SDL_Delay(delay);
}

static void	music_controls(int key, t_controls *controls, t_sdl *sdl)
{
	if (key == SDLK_p)
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
		show_data(info, sdl);
		gladiatorial_fight(&controls->play, info, sdl);
		SDL_UpdateWindowSurface(sdl->window); //draw surface
	}
	else if (key == SDLK_i && controls->speed > 0)
	{
		controls->speed -= 50;
		udpate_delay(controls->speed, sdl);
		SDL_UpdateWindowSurface(sdl->window); //draw surface
	}
	else if (key == SDLK_d && controls->speed < 1000)
	{
		controls->speed += 50;
		udpate_delay(controls->speed, sdl);
		SDL_UpdateWindowSurface(sdl->window); //draw surface
	}
	/*else if (key == SDLK_a) //temporary
	{
		//show = show == 0 ? 1 : 0;
		prepare_announcement(sdl);
		announce_winner(controls.seed++, (info->players)[info->last_live - 1], sdl);
		SDL_UpdateWindowSurface(sdl->window); //draw surface
		//sdl->speed = 150;
	}*/
	else if (key == SDLK_e) //temporary
		controls->exp = controls->exp == 0 ? 1 : 0;
	else
		music_controls(key, controls, sdl);
}

static void	take_game_action(t_controls *controls, t_info *info, t_sdl *sdl)
{
	//printf("play - %d\n", controls->play);
	if (controls->play == 1)
		update_for_one_round(controls->speed, &controls->play, info, sdl);
	else if (controls->play == -1 && controls->show_time != 0)
	{
		controls->speed = 150;
		controls->show_time--;
		epileptic_square(controls->seed++, sdl->render_info, sdl->surface, sdl);
		SDL_Delay(controls->speed);
		if (controls->show_time == 0)
		{
			prepare_announcement(sdl);
			announce_winner(controls->seed++,
				(info->players)[info->last_live - 1], sdl);
		}
		SDL_UpdateWindowSurface(sdl->window); //draw surface
	}
	/*if (controls->exp)
	{
		double q[256];
		SDL_Rect p;
		for(controls->i=256*!(controls->n); controls->i ; q[--(controls->i)]=rand()%65536*9.5874e-5); {
			SDL_FillRect(sdl->surface,0,controls->i=0); // clear view
			for(; controls->i < 256 ; controls->i++) {
				p.x = 560 + cos(q[controls->i]) * q[controls->i-1] * controls->n / 10; // first number currects the position (middle), division controls the size
				p.y = 560 + sin(q[controls->i]) * q[controls->i-1] * controls->n / 10; // first number currects the position (middle), division controls the size
				p.w = 2; // width of all little particles 
				p.h = 1; // height of all little particles
				SDL_FillRect(sdl->surface,&p,0xFFFFFF);//<< controls->r++);// for colorful effect replace color with 0xFFFFFF << r++, original - -n*67372030
			}
		}
		SDL_UpdateWindowSurface(sdl->window);
		SDL_Delay(50);
		printf("GOT OUT\n");
	}*/
			
}

void		redraw_range(int location, t_sdl *sdl)
{
	int start = location - 64 * 2 - 2;
	int i;
	int j = 0;;
	int x = NIBBLE_X_SHIFT + NIBBLE_WIDTH * (start % 64);
	int y = NIBBLE_Y_SHIFT + NIBBLE_HEIGHT * (start / 64);
	SDL_FillRect(sdl->surface,&((SDL_Rect){x, y, NIBBLE_WIDTH * 5, NIBBLE_HEIGHT * 5}),0); // clear view
	while (j < 5)
	{
		i = 0;
		while (i < 5)
		{
			update_byte(start + i + j * 64, sdl);
			i++;
		}
		j++;
	}
}

void		event_handler(t_info *info, t_sdl *sdl)
{
	int			key;
	SDL_Event	event;
	t_controls	controls;

	controls = (t_controls) {0, DEFAULT_GAME_SPEED, 20, 0, 0};
	//Mix_PlayMusic(sdl->main_theme, 1); // commented for no music while debugging
	SDL_Rect p;
	int i = 0, n = 63, r = 0;
	double q[256];
	int location = 224;
	int x = NIBBLE_X_SHIFT + NIBBLE_WIDTH * (location % 64) + 8;
	int y = NIBBLE_Y_SHIFT + NIBBLE_HEIGHT * (location / 64) + 8;
	while (1)
	{
		//take_game_action(&controls, info, sdl);
		if (controls.exp)
		{
			printf("n - %d ", n);
			n = -~n%64;
			printf("N - %d\n", n);
			for(i=256*!n; i ; q[--i]=rand()%65536*9.5874e-5);
			//SDL_FillRect(sdl->surface,&((SDL_Rect){560 - 40, 560 - 40, 80, 80}),0); // clear view
			redraw_range(location, sdl);
			if (n == 63)
				controls.exp = controls.exp == 0 ? 1 : 0;
			else {
				for(i = 0; i < 256 ; i++) {
					p.x = x + cos(q[i]) * q[i-1] * n / 10; // first number currects the position (middle), division controls the size
					p.y = y + sin(q[i]) * q[i-1] * n / 10; // first number currects the position (middle), division controls the size
					p.w = 2; // width of all little particles 
					p.h = 1; // height of all little particles
					SDL_FillRect(sdl->surface,&p,0xFFFFFF << r++);// for colorful effect replace color with 0xFFFFFF << r++, original - -n*67372030
				}
			}
			SDL_UpdateWindowSurface(sdl->window);
			SDL_Delay(50);
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
				if (controls.play != -1)
					game_controls(key, &controls, info, sdl);
			}
		}
	}
}
