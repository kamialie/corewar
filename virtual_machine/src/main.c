/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 13:34:54 by rgyles            #+#    #+#             */
/*   Updated: 2019/11/10 16:56:50 by bdudley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void 	init_info(t_info *info)
{
	int		i;

	info->dump = -1;
	i = -1;
	while (++i < MAX_PLAYERS)
	{
		(info->players)[i].magic = 0;
		(info->players)[i].prog_size = 0;
		ft_bzero((info->players)[i].prog_name, PROG_NAME_LENGTH + 1);
		ft_bzero((info->players)[i].comment, COMMENT_LENGTH + 1);
	}
}

int	main(int argc , char *argv[])
{
	t_info		info;

	init_arena();
	init_info(&info);
	read_arg(&info, argc, argv);
	int i;
	i = -1;
	while (++i < MAX_PLAYERS)
	{
		printf("%d) name : |%s| comment : |%s| prog_size : |%d|\n", i + 1, (info.players)[i].prog_name, (info.players)[i].comment, (info.players)[i].prog_size);
	}
	return (0);
}
