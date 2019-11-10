/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_arena.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 17:09:14 by rgyles            #+#    #+#             */
/*   Updated: 2019/11/10 17:24:37 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//TODO collect line to buffer for output, instead of each pair seperately

#include "corewar.h"

void	print_bit(unsigned char bit)
{
	if (bit < 10)
		ft_putchar(bit + 48);
	else if (bit == 10)
		ft_putchar('a');
	else if (bit == 11)
		ft_putchar('b');
	else if (bit == 12)
		ft_putchar('c');
	else if (bit == 13)
		ft_putchar('d');
	else if (bit == 14)
		ft_putchar('e');
	else if (bit == 15)
		ft_putchar('f');
}

/*
** view 32 bytes as a row
** pair of digits represents a byte(unsigned char), e.g. fa
** first half is low part, second half is high part of the byte
*/
void	print_arena_row(unsigned char *arena, int row)
{
	int i;
	int	total;

	total = (row + 1) * 32;
	i = total - 32;
	print_bit((arena[i] & 0xf) >> 4);
	print_bit(arena[i] & 0xf);
	while (i++ < total)
	{
		ft_putchar(' ');
		print_bit((arena[i] & 0xf0) >> 4);
		print_bit(arena[i] & 0xf);
	}
}

/*
** label is short int (2 bytes)
** print each 4 bits seperatly using char pointer
*/
void	print_row_label(unsigned short int row_label)
{
	unsigned char	*label;

	label = (unsigned char *)&row_label;
	ft_putstr("0x");
	print_bit((*(label + 1) & 0xf0) >> 4);
	print_bit(*(label + 1) & 0xf);
	print_bit((*label & 0xf0) >> 4);
	print_bit(*label & 0xf);
	ft_putstr(": ");
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
	ft_putchar('\n');
	while (row++ < total)
	{
		print_row_label(row_label);
		row_label += 32;
		print_arena_row(arena, row);
		ft_putchar('\n');
	}
}
