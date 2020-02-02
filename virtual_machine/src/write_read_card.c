/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_read_card.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 19:09:46 by bdudley           #+#    #+#             */
/*   Updated: 2020/02/02 19:09:48 by bdudley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		read_card(void *dst, void *src, short int value, int length)
{
	short int	size;

	size = (MEM_SIZE - value) > length ? length : MEM_SIZE - value;
	if (size > 0)
		ft_memcpy(dst, src + value, size);
	if (size < length)
		ft_memcpy(dst + size, src, length - size);
}

void		write_card(void *dst, void *src, short int value, int length)
{
	short int	size;

	size = (MEM_SIZE - value) > length ? length : MEM_SIZE - value;
	if (size > 0)
		ft_memcpy(dst + value, src, size);
	if (size < length)
		ft_memcpy(dst, src + size, length - size);
}
