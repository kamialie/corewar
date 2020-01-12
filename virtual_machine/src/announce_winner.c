/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   announce_winner.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 20:00:09 by rgyles            #+#    #+#             */
/*   Updated: 2020/01/12 15:01:42 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visual.h"
#include "corewar.h"

static void	set_new_font_size(t_render *render_info) //need to add check
{
	TTF_Font *font;

	font = render_info->font;
	TTF_CloseFont(font); //free memory used by font
	font = TTF_OpenFont(FONT_PATH, 50); //open font
	TTF_SetFontStyle(font, TTF_STYLE_BOLD);
	render_info->font = font;
}

/*
** changed fond (its size) in the middle
*/

void		prepare_announcement(t_sdl *sdl)
{
	SDL_Rect	rect;
	t_render	*render_info;

	rect.x = 2;
	rect.y = 2;
	rect.w = 1350;
	rect.h = 1155;
	SDL_FillRect(sdl->surface, &rect, 0);
	render_info = sdl->render_info;
	set_new_font_size(render_info);
	render_info->font_color = sdl->colors[WHITE];
	render_info->back_color = sdl->colors[BLACK];
}

/*
** print player's comment or not?
*/

void		announce_winner(int seed, header_t player, t_sdl *sdl)
{
	t_render	*render_info;
	SDL_Surface	*surface;

	render_info = sdl->render_info;
	surface = sdl->surface;
	render_info->rect.x = 500;
	render_info->rect.y = 500;
	render_text("Winner is:", render_info, surface);
	render_info->rect.y += 100;
	render_text(player.prog_name, render_info, surface);
}
