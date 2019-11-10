/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 16:27:43 by bdudley           #+#    #+#             */
/*   Updated: 2019/11/10 17:10:23 by bdudley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "corewar.h"

unsigned int	get_magic(t_info *info, int fd)
{
	unsigned int	magic;
	unsigned int	buf;

	buf = 0;
	magic = 0;
	if (read(fd, &buf, 4) == -1)
		error(4); //Ошибка, пустой файл или директория, недостаточно данных
	magic += ((buf & 0xff) << (8 * 3));
	magic += ((buf & 0xff00) << (8 * 1));
	magic += ((buf & 0xff0000) >> (8 * 1));
	magic += ((buf & 0xff000000) >> (8 * 3));
	if (magic != COREWAR_EXEC_MAGIC)
		error(5); //Ошибка, этот файл не бинарный
	return (magic);
}

unsigned int	get_prog_size(t_info *info, int fd)
{
	unsigned int	prog_size;
	unsigned int	buf;

	buf = 0;
	prog_size = 0;
	if (read(fd, &buf, 4) == -1)
		error(4); //Ошибка чтения, недостаточно данных
	prog_size += ((buf & 0xff) << (8 * 3));
	prog_size += ((buf & 0xff00) << (8 * 1));
	prog_size += ((buf & 0xff0000) >> (8 * 1));
	prog_size += ((buf & 0xff000000) >> (8 * 3));
	return (prog_size);
}

//Считывает бинарный файл в структуру
void			read_file(t_info *info, char *file_name, int number)
{
	int				fd;

	if ((fd = open(file_name, O_RDONLY)) == -1)
		error(0); //Ошибка, файл не открылся
	if (number >= 0 && (info->players)[number].magic == COREWAR_EXEC_MAGIC)
		error(3); //Ошибка, чемпион с таким идентификатором уже есть
	if (number < 0)
	{
		number = 0;
		while ((info->players)[number].magic == COREWAR_EXEC_MAGIC)
			++number;
	}
	(info->players)[number].magic = get_magic(info, fd);
	if (read(fd, (info->players)[number].prog_name, PROG_NAME_LENGTH) == -1)
		error(4); //Ошибка чтения, недостаточно данных
	if (lseek(fd, 4, SEEK_CUR) == -1)
		error(4); //Ошибка чтения, недостаточно данных
	(info->players)[number].prog_size = get_prog_size(info, fd);
	if (read(fd, (info->players)[number].comment, COMMENT_LENGTH) == -1)
		error(4); //Ошибка чтения, недостаточно данных
	if (lseek(fd, 4, SEEK_CUR) == -1)
		error(4); //Ошибка чтения, недостаточно данных
	close(fd);
}

//Проверяет, что все чемпионы имеют расширение .cor
static int		count_champion(t_info *info, int argc, char *argv[])
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
			error(2); //Ошибка, невалидный чемпион(нет расширения .cor)
	}
	return (count);
}

//Проверяет валидность аргументов  и парсит флаги
void			read_arg(t_info *info, int argc, char *argv[])
{
	int		i;
	int		number;
	int 	count;

	i = 0;
	count = count_champion(info, argc, argv);
	while (++i < argc)
	{
		if (!ft_strcmp(argv[i], DUMP) && i + 1 < argc)
			info->dump = ft_atoi(argv[++i]);
		else if (!ft_strcmp(argv[i], N) && i + 2 < argc)
		{
			if ((number = ft_atoi(argv[++i])) < 1 || number > count)
				error(1); // Ошибка, после n указан невалидный аргумент(число меньше 1  или больше поданного количества чемпионов)
			read_file(info, argv[++i], number - 1);
		}
	}
	i = 0;
	while (++i < argc)
	{
		if (!ft_strcmp(argv[i], DUMP) && i + 1 < argc)
			++i;
		else if (!ft_strcmp(argv[i], N) && i + 2 < argc)
			i += 2;
		else
			read_file(info, argv[i], -1);
	}
}