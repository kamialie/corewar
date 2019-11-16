/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 15:50:24 by rgyles            #+#    #+#             */
/*   Updated: 2019/11/13 16:14:22 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visual.h"

void	event_handler(t_sdl *sdl)
{
	int	key;
	SDL_Event event;

	(void)sdl;
	while (1)
	{
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
			}
		}
	}
}