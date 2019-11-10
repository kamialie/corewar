/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 15:09:32 by rgyles            #+#    #+#             */
/*   Updated: 2019/11/10 17:29:26 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "libft.h"

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
