/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 16:25:36 by rgyles            #+#    #+#             */
/*   Updated: 2019/11/13 16:44:24 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visual.h"

void	draw(t_sdl *sdl)
{
	SDL_UpdateWindowSurface(sdl->window);
	event_handler(sdl);
	SDL_FreeSurface(sdl->surface);
	SDL_DestroyWindow(sdl->window);
	SDL_Quit();
}
