/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 16:27:43 by bdudley           #+#    #+#             */
/*   Updated: 2019/11/10 15:05:45 by bdudley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "corewar.h"


void			read_file(t_info *info, char *file_name, int number)
{
	int				fd;
	unsigned int	magic;
	unsigned int	tmp;


	if ((fd = open(file_name, O_RDONLY)) == -1)
		error(0); //Ошибка, файл не открылся
	if (number >= 0 && (info->players)[number].magic == COREWAR_EXEC_MAGIC)
		error(3); //Ошибка, чемпион с таким идентификатором уже есть
	else
	{
		number = 0;
		while ((info->players)[number].magic == COREWAR_EXEC_MAGIC)
			++number;
	}
	//(info->players)[number].magic = get_magic(info, );
	if (read(fd, &magic, 4) == -1)
		error(4); //Ошибка, пустой файл или директория
	tmp = 0;
	tmp += ((magic & 0xff) << (8 * 3));
	tmp += ((magic & 0xff00) << (8 * 1));
	tmp += ((magic & 0xff0000) >> (8 * 1));
	tmp += ((magic & 0xff000000) >> (8 * 3));

	printf("magic %u and %u\n", tmp, COREWAR_EXEC_MAGIC);
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