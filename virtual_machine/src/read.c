/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 16:27:43 by bdudley           #+#    #+#             */
/*   Updated: 2019/11/12 18:05:11 by bdudley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "corewar.h"

static unsigned int	get_prog_size(t_info *info, int fd)
{
	unsigned int	prog_size;
	unsigned int	buf;

	buf = 0;
	prog_size = 0;
	if (read(fd, &buf, 4) == -1)
		error(4);
	prog_size += ((buf & 0xff) << (8 * 3));
	prog_size += ((buf & 0xff00) << (8 * 1));
	prog_size += ((buf & 0xff0000) >> (8 * 1));
	prog_size += ((buf & 0xff000000) >> (8 * 3));
	if (prog_size > CHAMP_MAX_SIZE)
		error(6);
	return (prog_size);
}

static void			read_arena(t_info *info, int fd, int number, int count)
{
	unsigned int	shift;

	shift = (MEM_SIZE / count) * number;
	if (read(fd, info->arena + shift, CHAMP_MAX_SIZE) == -1)
		error(4);
}

static void			read_file(t_info *info, char *file_name,
					int number, int count)
{
	int				fd;

	if ((fd = open(file_name, O_RDONLY)) == -1)
		error(0);
	if (number >= 0 && (info->players)[number].magic == COREWAR_EXEC_MAGIC)
		error(3);
	if (number < 0)
	{
		number = 0;
		while ((info->players)[number].magic == COREWAR_EXEC_MAGIC)
			++number;
	}
	(info->players)[number].magic = get_magic(info, fd);
	if (read(fd, (info->players)[number].prog_name, PROG_NAME_LENGTH) == -1)
		error(4);
	if (lseek(fd, 4, SEEK_CUR) == -1)
		error(4);
	(info->players)[number].prog_size = get_prog_size(info, fd);
	if (read(fd, (info->players)[number].comment, COMMENT_LENGTH) == -1)
		error(4);
	if (lseek(fd, 4, SEEK_CUR) == -1)
		error(4);
	read_arena(info, fd, number, count);
	close(fd);
}

static int			count_champion(t_info *info, int argc, char *argv[])
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (++i < argc)
	{
		if (!ft_strcmp(argv[i], DUMP) && i + 1 < argc)
			++i;
		else if (!ft_strcmp(argv[i], N) && i + 2 < argc
		&& ft_strrchr(argv[i + 2], '.')
		&& !ft_strcmp(COR, ft_strrchr(argv[i + 2], '.')))
		{
			i += 2;
			count++;
		}
		else if (ft_strrchr(argv[i], '.') &&
		!ft_strcmp(COR, ft_strrchr(argv[i], '.')))
			count++;
		else
			error(2);
	}
	info->last_live = count;
	info->count_process = count;
	return (count);
}

void				read_arg(t_info *info, int argc, char *argv[])
{
	int				i;
	int				number;
	int				count;

	i = 0;
	count = count_champion(info, argc, argv);
	while (++i < argc)
	{
		if (!ft_strcmp(argv[i], DUMP) && i + 1 < argc)
			info->dump = ft_atoi(argv[++i]);
		else if (!ft_strcmp(argv[i], N) && i + 2 < argc)
		{
			if ((number = ft_atoi(argv[++i])) < 1 || number > count)
				error(1);
			read_file(info, argv[++i], number - 1, count);
		}
	}
	i = 0;
	while (++i < argc)
		if (!ft_strcmp(argv[i], DUMP) && i + 1 < argc)
			++i;
		else if (!ft_strcmp(argv[i], N) && i + 2 < argc)
			i += 2;
		else
			read_file(info, argv[i], -1, count);
}