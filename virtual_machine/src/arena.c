/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 15:09:32 by rgyles            #+#    #+#             */
/*   Updated: 2019/11/08 18:36:07 by bdudley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "libft.h"

void	init_arena(void)
{
	char arena;

	ft_putchar('a');
	arena = (char)malloc(MEM_SIZE);
	printf("Initializing arena\n");
}
