/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 16:27:43 by bdudley           #+#    #+#             */
/*   Updated: 2019/11/08 19:47:13 by bdudley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "corewar.h"

void	read_file(t_info *info, char *file_name)
{
	int		fd;

	if ((fd = open(file_name, O_RDONLY)) == -1)
		error(0);
	close(fd);
}

void	read_arg(t_info *info, int argc, char *argv[])
{
	int		i;
	int		number;

	i = 0;
	while (++i < argc)
	{
		if (!ft_strcmp(argv[i], DUMP) && i + 1 < argc)
		{
			info->dump = ft_atoi(argv[++i]);
		}
		else if (!ft_strcmp(argv[i], N) && i + 2 < argc)
		{
			if ((number = ft_atoi(argv[++i])) < 1)
				error(1);
			read_file(info, argv[++i]);
		}
	}
}