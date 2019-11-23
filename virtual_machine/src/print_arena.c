/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_arena.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 17:09:14 by rgyles            #+#    #+#             */
/*   Updated: 2019/11/23 19:23:48 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//TODO collect line to buffer for output, instead of each pair seperately

#include "corewar.h"

//exists in draw.c
/*char	get_nibble(unsigned char bit)
{
	if (bit < 10)
		return (bit + 48);
	else if (bit == 10)
		return('a');
	else if (bit == 11)
		return('b');
	else if (bit == 12)
		return('c');
	else if (bit == 13)
		return('d');
	else if (bit == 14)
		return('e');
	else
		return('f');
}*/

/*
** label is short int (2 bytes)
** print each 4 bits seperatly using char pointer
*/
void	print_row_label(unsigned short int row_label)
{
	unsigned char	*num;
	char	label[9];
	char	*str;

	num = (unsigned char *)&row_label;
	str = label;
	*str++ = '0';
	*str++ = 'x';
	*str++ = get_nibble((*(num + 1) & 0xf0) >> 4);
	*str++ = get_nibble(*(num + 1) & 0xf);
	*str++ = get_nibble((*num & 0xf0) >> 4);
	*str++ = get_nibble(*num & 0xf);
	*str++ = ':';
	*str++ = ' ';
	*str = '\0';
	ft_putstr(label);
}

/*
** view 32 bytes as a row
** pair of digits represents a byte(unsigned char), e.g. fa
** first half is low part, second half is high part of the byte
*/
void	print_arena_row(unsigned char *arena, int row)
{
	int 	i;
	int		last;
	char	line[LINE_SIZE];
	char	*str;

	last = (row + 1) * 32;
	i = last - 32;
	str = line;
	*str++ = get_nibble((arena[i] & 0xf0) >> 4);
	*str++ = get_nibble(arena[i] & 0xf);
	while (++i < last)
	{
		*str++ = ' ';
		*str++ = get_nibble((arena[i] & 0xf0) >> 4);
		*str++ = get_nibble(arena[i] & 0xf);
	}
	*str++ = '\n';
	*str = '\0';
	ft_putstr(line);
}


void	print_arena(unsigned char *arena)
{
	int	row;
	int	total;
	unsigned short int	row_label;

	row = 0;
	total = MEM_SIZE / 32 - 1;
	row_label = 0;
	print_row_label(row_label);
	row_label += 32;
	print_arena_row(arena, row);
	while (row++ < total)
	{
		print_row_label(row_label);
		row_label += 32;
		print_arena_row(arena, row);
	}
}
