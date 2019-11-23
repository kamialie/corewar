/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_shapes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 15:15:47 by rgyles            #+#    #+#             */
/*   Updated: 2019/11/23 16:32:17 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visual.h"

void	draw_vertical_line(int x, int h, int color, int *img_data)
{
	int	y;

	y = 0;
	while (y < h)
	{
		img_data[y * WIN_WIDTH + x] = color;
		++y;
	}
}

void	draw_horizontal_line(int y, int w, int color, int	*img_data)
{
	int	x;

	x = 0;
	while (x < w)
	{
		img_data[y * WIN_WIDTH + x] = color;
		++x;
	}
}

void	draw_square(t_square sq_info, int *img_data)
{
	draw_vertical_line(sq_info.x0, sq_info.y0, sq_info.color, img_data);
	draw_vertical_line(sq_info.x0 + 1, sq_info.y0, sq_info.color, img_data);
	draw_vertical_line(sq_info.x1, sq_info.y0, sq_info.color, img_data);
	draw_vertical_line(sq_info.x1 - 1, sq_info.y0, sq_info.color, img_data);
	draw_horizontal_line(sq_info.y1, sq_info.x1, sq_info.color, img_data);
	draw_horizontal_line(sq_info.y1 + 1, sq_info.x1, sq_info.color, img_data);
	draw_horizontal_line(sq_info.y0, sq_info.x1, sq_info.color, img_data);
	draw_horizontal_line(sq_info.y0 - 1, sq_info.x1, sq_info.color, img_data);
}
