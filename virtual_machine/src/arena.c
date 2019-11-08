/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 15:09:32 by rgyles            #+#    #+#             */
/*   Updated: 2019/11/08 17:46:44 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "op.h"
#include "libft.h"

void	init_arena(void)
{
	char arena;

	ft_putchar('a');
	arena = (char)malloc(MEM_SIZE);
	printf("nitializing arena\n");
}
