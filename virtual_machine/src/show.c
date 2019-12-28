/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 20:00:07 by rgyles            #+#    #+#             */
/*   Updated: 2019/12/28 20:46:53 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sdl_struct.h"
#include "op.h"
#include "visual.h"

void	fill_in_vertial(int value, int index, int length, unsigned char *replica)
{
	int i;

	i = -1;
	while (++i < length)
		replica[index + i * 64] = value;
}

void	fill_in_horizontal(int value, int index, int length, unsigned char *replica)
{
	int i;

	i = -1;
	while (++i < length)
		replica[index++] = value;
}

void	form_squares(int seed, t_sdl *sdl)
{
	int start;
	int shift;
	int	length;

	start = 0;
	length = 64; //side of square
	shift = 65; // square side + 1
	while (start < MEM_SIZE / 2) // median
	{
		fill_in_vertial(seed % 5, start, length, sdl->replica);
		fill_in_vertial(seed % 5, start + length - 1, length, sdl->replica);
		fill_in_horizontal(seed % 5, start, length, sdl->replica);
		fill_in_horizontal(seed % 5, start + (length - 1) * 64, length, sdl->replica);
		++seed;
		start += shift;
		length -= 2;
	}
}

void	epileptic_square(int seed, t_sdl *sdl)
{
	int			index;
	int			end_of_row;
	int			row;
	t_render	*render_info;
	SDL_Surface	*surface;

	form_squares(seed, sdl);
	index = 0;
	set_nibble_for_render(index, EMPTY, 0, sdl);
	render_info = sdl->render_info;
	surface = sdl->surface;
	row = index / 64;
	end_of_row = (row + 1) * 64;
	while (index < MEM_SIZE)
	{
		while (index < end_of_row)
		{
			render_info->font_color = sdl->colors[sdl->replica[index] + FONT_COLOR];
			draw_byte(sdl->arena[index++], render_info, surface);
			render_info->rect.x += NIBBLE_WIDTH;
		}
		render_info->rect.y += NIBBLE_HEIGHT;
		render_info->rect.x = NIBBLE_X_SHIFT;
		end_of_row = (++row + 1) * 64;
		index = end_of_row - 64;
	}
}
