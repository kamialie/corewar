/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 15:09:32 by rgyles            #+#    #+#             */
/*   Updated: 2019/11/10 17:05:40 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "op.h"
#include "libft.h"

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

void	print_row_label(unsigned short int row_label)
{
	unsigned char	*label;

	label = (unsigned char *)&row_label;
	ft_putstr("0x");
	print_bit((*(label + 1) & 0xf0) >> 4);
	print_bit(*(label + 1) & 0xf);
	print_bit((*label & 0xf0) >> 4);
	print_bit(*label & 0xf);
	//printf("row_label - %d\n", row_label);
	//printf("label - %d\n", *(label + 0));
	ft_putstr(": ");
}

void	print_arena(unsigned char *arena)
{
	int	row;
	int	total;
	unsigned short int	row_label;

	row = 0;
	total = MEM_SIZE / 32 - 1;
	//total = 2;
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
	//printf("cell - %hx\n", arena[0]);
	//print_arena_row(arena, 0);
	/*while (i < row)
	{
		print_bit((arena[cell] & 0xf) >> 4);
		print_bit(arena[cell] & 0xf);
		++cell;
		while (cell < column)
		{
			ft_putchar(' ');
			print_bit((arena[cell] & 0xf0) >> 4);
			print_bit(arena[cell] & 0xf);
			++cell;
		}
		++i;
		ft_putchar('\n');
	}*/
}

void	init_arena(void)
{
	unsigned char	ch;
	unsigned char	*arena;

	arena = (unsigned char *)malloc(MEM_SIZE);
	
	//TMP
	arena[0] = 0x0f;
	arena[1] = 0x12;
	unsigned char high;
	unsigned char low;
	high = (arena[1] & 0xf0) >> 4;
	low = arena[1] & 0xf;
	//printf("%x%x\n", high, low);

	//print_row_label(35);
	//END
	//printf("initializing arena\n");
	print_arena(arena);
}
