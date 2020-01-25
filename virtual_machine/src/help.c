/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 17:51:50 by bdudley           #+#    #+#             */
/*   Updated: 2019/11/08 19:15:48 by bdudley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void				error(int err)
{
	if (err == 0)
		perror("File did not open\n");
	else if (err == 1)
		perror("Invalid argument after n - number is less \
than 1 or greater than the number of champions\n");
	else if (err == 2)
		perror("Invalid champion - no .cor extension found\n");
	else if (err == 3)
		perror("Champion with this ID already exists\n");
	else if (err == 4)
		perror("Reading error - not enough data\n");
	else if (err == 5)
		perror("Not a binary file\n");
	else if (err == 6)
		perror("File exceeds maximum size for champion\n");
	else if (err == 7)
		perror("No champions are found\n");
	else if (err == 8)
		perror("Memory allocation error\n");
	else if (err == 9)
		perror("Found extra data\n");
	else if (err == 10)
		perror("Actual program size does not equal to declared size\n");
	exit(1);
}

unsigned int		get_magic(t_info *info, int fd)
{
	unsigned int	magic;
	unsigned int	buf;

	buf = 0;
	magic = 0;
	if (read(fd, &buf, 4) == -1)
		error(4);
	magic += ((buf & 0xff) << (8 * 3));
	magic += ((buf & 0xff00) << (8 * 1));
	magic += ((buf & 0xff0000) >> (8 * 1));
	magic += ((buf & 0xff000000) >> (8 * 3));
	if (magic != COREWAR_EXEC_MAGIC)
		error(5);
	return (magic);
}

void				shift_next_op(unsigned char code_arg,
		short int num_fun, t_processes **prs, t_sdl *sdl)
{
	int				skiped_bytes;
	short int		current_location;

	current_location = (*prs)->index;
	skiped_bytes = get_bytes_to_skip(num_fun, code_arg);
	if (sdl != NULL)
		move_cursor(current_location, skiped_bytes, IND((*prs)->reg[0]), sdl);
	(*prs)->index = (current_location + skiped_bytes) % MEM_SIZE;
}

void				present_champion(header_t *players)
{
	int				i;

	i = -1;
	printf("Introducing contestants...\n");
	while (++i < MAX_PLAYERS && players[i].magic == COREWAR_EXEC_MAGIC)
	{
		printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n", i + 1,
				players[i].prog_size, players[i].prog_name, players[i].comment);
	}
}
