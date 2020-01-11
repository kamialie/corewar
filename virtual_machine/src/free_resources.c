/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_resources.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 14:49:35 by rgyles            #+#    #+#             */
/*   Updated: 2020/01/11 14:49:37 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	free_music(t_sdl *sdl)
{
	Mix_FreeChunk(sdl->live_effect); //free sound effect
	Mix_CloseAudio(); //close mixer
    Mix_FreeMusic(sdl->main_theme); //free music
	Mix_Quit(); // clear all library handles created by Mix_Init
}

void	free_ttf(t_sdl *sdl)
{
	TTF_CloseFont(sdl->render_info->font); //free memory used by font
	TTF_Quit();
}

void	free_resources(t_sdl *sdl)
{
	free_music(sdl);
	free_ttf(sdl);
	free(sdl->render_info); // free render helper struct
	SDL_DestroyWindow(sdl->window);
	SDL_Quit();
}
