/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 16:27:43 by bdudley           #+#    #+#             */
/*   Updated: 2019/11/08 17:24:57 by bdudley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "corewar.h"

void	read_file(char *file_name)
{
	int		fd;

	if (fd = open(file_name, O_RDONLY) == -1)
		strerror(errno);
	printf("File is open\n");
}

void	read_arg(int argc, char *argv[])
{
	int		i;
	int 	dump;

	i = 0;
	while (++i < argc)
	{
		if (ft_strcmp(argv[i], DUMP) && i + 1 < argc)
		{
			if ((dump = ft_atoi(argv[++i])) )
			{

			}
			printf("Is a -dump\n");
		}
		else if (ft_strcmp(argv[i], N) && i + 2 < argc)
		{
			printf("Is a -n\n");
		}
		else
			read_file(argv[i]);
	}
}