/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 13:34:54 by rgyles            #+#    #+#             */
/*   Updated: 2019/11/24 18:56:34 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visual.h"
#include "corewar.h"


void	present_champion(header_t *players)
{
	int i;

	i = -1;
	printf("Introducing contestants...\n");
	while (++i < MAX_PLAYERS && players[i].magic == COREWAR_EXEC_MAGIC)
	{
		printf("* Player %d, weighing %d bytes, %s (%s) !\n", i + 1,
				players[i].prog_size, players[i].prog_name, players[i].comment);
	}
}

void 	init_info(t_info *info)
{
	int		i;

	info->arena = (unsigned char *)malloc(MEM_SIZE); //check NULL
	ft_bzero(info->arena, MEM_SIZE);
	info->dump = -1;
	info->cycle_to_die = CYCLE_TO_DIE;
	info->count_cycles = 0;
	info->count_live = 0;
	info->count_check = 0;
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
	t_sdl		sdl;

	if (argc < 2)
		error(8); //Ошибка, нет игроков
	init_info(&info);
	read_arg(&info, argc, argv);
	if (init_sdl(&sdl))
		return (1);
	initialize_visual_arena(&sdl, &info);
	present_champion(info.players);
	create_processes(&info);
//	unsigned int *ptr;
//	ptr = (unsigned int *)(info.arena);
//	printf("%d %d %d %d\n", *(info.arena), *(info.arena + 1), *(info.arena + 2), *(info.arena + 3));
//	printf("result %u\n", *ptr);
	gladiatorial_fight(&info);
	printf("Contestant %d, %s, has won !\n", info.last_live, (info.players)[info.last_live - 1].prog_name);
	//print_arena(info.arena);
	return (0);
}
