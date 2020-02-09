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

void		usage(void)
{
	/*
	 * Виртуальная машина:
	 * Для того, чтобы заупстить игру используй: ./corewar [путь до чемпиона] ...
	 * Количество возможных чемпионов ограничевается константой MAX_PLAYERS.
	 * Для того, чтобы оставновить игру на каком-то определенном цикле и вывести текущую арену на экран используй флаг -dump [цикл]
	 * Для того, чтобы увидеть эпичную игру в действии используй флаг -dump -666, который запустит визуализацию игры и отладочный мод
	 * Используй чемпионов сгенирированный программой ./asm
	 * Для того, чтобы вручную задать порядок игроков используй флаг ./corewar -n [номер] [путь до чемпиона].
	 * Все чемпионы, которым не задали номер получать один из оставшихся.
	 */
	exit(1);
}
