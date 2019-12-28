/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   announce_winner.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 20:00:09 by rgyles            #+#    #+#             */
/*   Updated: 2019/12/28 20:58:38 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visual.h"
#include "corewar.h"

void	announce_winner(header_t player, t_sdl *sdl)
{
	//TTF_Font	*font;
	SDL_Rect	rect;

	rect.x = 2;
	rect.y = 2;
	rect.w = 1350;
	rect.h = 1155;
	//font = TTF_OpenFont(FONT_PATH, 25); //open font
	//TTF_SetFontStyle(font, TTF_STYLE_BOLD);
	//clear_rect(
	SDL_FillRect(sdl->surface, &rect, 0);
	sdl->render_info->font_color = sdl->colors[WHITE];
	sdl->render_info->back_color = sdl->colors[BLACK];
	sdl->render_info->rect.x = 500;
	sdl->render_info->rect.y = 500;

	render_text("Winner is:", sdl->render_info, sdl->surface);
	sdl->render_info->rect.y += 100;
	render_text(player.prog_name, sdl->render_info, sdl->surface);
	sdl->render_info->rect.y += 100;
	render_text(player.comment, sdl->render_info, sdl->surface);
	SDL_UpdateWindowSurface(sdl->window); //draw surface
}
