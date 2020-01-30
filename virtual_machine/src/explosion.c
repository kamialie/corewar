/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   explosion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 17:22:02 by rgyles            #+#    #+#             */
/*   Updated: 2020/01/25 14:54:11 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sdl_struct.h"
#include "visual.h"
#include "corewar.h"

/*
** free space where the explosion takes place
*/

void		redraw_range(int start, SDL_Rect *r, t_sdl *sdl)
{
	int i;
	int j;

	j = -1;
	SDL_FillRect(sdl->surface, r, 0);
	while (++j < 5)
	{
		i = -1;
		while (++i < 5)
			update_byte(start + i + j * 64, sdl);
	}
}

/*
** 8 is the shift to move to nibble's center
** rect to redraw region, 5 x 5 square
*/

t_explosion	*create_explosion(int location)
{
	int			start;
	t_explosion *e;

	e = malloc(sizeof(t_explosion));
	ft_bzero(e, sizeof(e));
	start = location - 64 * 2 - 2;
	e->rect.x = NIBBLE_X_SHIFT + NIBBLE_WIDTH * (start % 64);
	e->rect.y = NIBBLE_Y_SHIFT + NIBBLE_HEIGHT * (start / 64);
	e->rect.w = NIBBLE_WIDTH * 5;
	e->rect.h = NIBBLE_HEIGHT * 5;
	e->start = start;
	e->location = location;
	e->x = NIBBLE_X_SHIFT + NIBBLE_WIDTH * (location % 64) + 8;
	e->y = NIBBLE_Y_SHIFT + NIBBLE_HEIGHT * (location / 64) + 8;
	e->next = NULL;
	return (e);
}

void		add_explosion(t_explosion *e, t_explosion **head)
{
	if (*head == NULL)
		*head = e;
	else
	{
		e->next = *head;
		*head = e;
	}
}

void		remove_explosion(t_explosion *e, t_explosion **head)
{
	t_explosion *cur;

	cur = *head;
	while (cur != e)
		cur = cur->next;
	*head = e->next;
	free(e);
}

/*
** MAGIC!
** rect height and width are for each particle
** rect x and y division controls the size of explosion
** addition controls position
*/

void		draw_explosion(t_explosion *e, t_sdl *sdl)
{
	int			i;
	SDL_Rect	rect;

	while (e)
	{
		i = 256 * !(e->n);
		while (i)
			e->q[--i] = rand() % 65536 * 9.5874e-5;
		redraw_range(e->start, &(e->rect), sdl);
		if (++e->n == 43)
			remove_explosion(e, &sdl->head_explosion);
		else
		{
			i = -1;
			while (++i < 256)
			{
				rect.x = e->x + cos(e->q[i]) * e->q[i - 1] * e->n / 10;
				rect.y = e->y + sin(e->q[i]) * e->q[i - 1] * e->n / 10;
				rect.w = 2;
				rect.h = 1;
				SDL_FillRect(sdl->surface, &rect, 0xFFFFFF << e->r++);
			}
		}
		e = e->next;
	}
}