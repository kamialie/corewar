/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 15:09:32 by rgyles            #+#    #+#             */
/*   Updated: 2019/11/08 20:11:27 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "op.h"
#include "libft.h"

void	print_cell(char *cell)
{
	int i;
	unsigned char	symbol;

	i = 0;
	symbol = *cell;
	while (i < 2)
	{
		if (symbol < 10)
			ft_putchar(symbol % 10 + 48);
		else if (symbol == 10)
			ft_putchar('a');
		else if (symbol == 11)
			ft_putchar('b');
		else if (symbol == 12)
			ft_putchar('c');
		else if (symbol == 13)
			ft_putchar('d');
		else if (symbol == 14)
			ft_putchar('e');
		else if (symbol == 15)
			ft_putchar('f');
		++i;
		symbol = *(cell + 1);
	}
	ft_putchar(' ');
}

void	print_arena(unsigned short int *arena)
{
	int	cell;
	int	row;

	cell = 0;
	row = 32;
	printf("cell - %hx\n", arena[0]);
	while (cell < row)
	{
		//printf("%hx ", arena[cell]);
		print_cell((char *)&arena[cell]);
		++cell;
	}
}

void	init_arena(void)
{
	unsigned char ch;
	unsigned char	*tmp;
	unsigned short int *arena;

	arena = (unsigned short int *)malloc(MEM_SIZE);
	tmp = (char *)arena;
	arena[0] = 0xf0;
	arena[1] = 0xf;
	

	unsigned short int kek = arena[0];
	printf("%c\n", (unsigned char)kek % 10 + 48);
	for (int i = 0; i < 8; i++)
	{
		printf("%d", kek % 2);
		kek = kek / 2;
	}

	//printf("letter - %d\n", *tmp);
	//printf("letter - %d\n", *(arena+1));
	printf("\ninitializing arena\n");
	printf("size - %zu\n", sizeof(char));
	print_arena(arena);
}
