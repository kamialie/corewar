/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 13:34:54 by rgyles            #+#    #+#             */
/*   Updated: 2019/12/14 16:50:04 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visual.h"
#include "corewar.h"


//переместить
int     get_bytes_to_skip(int num, unsigned char code_arg)
{
    int     i;
    int     summ;
    char    copy;

    i = -1;
    summ = 2;
    while (++i < g_op_tab[num].count_args)
    {
        copy = (code_arg >> (6 - i * 2)) & 00000011;
        if (copy == 3)
            summ += 2;
        else if (copy== 1)
            summ += 1;
        else if (copy == 2)
            summ += g_op_tab[num].t_dir_size;
        copy = code_arg;
    }
    return (summ);
}

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
	info->i = -1;
	info->processes = NULL;
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
	present_champion(info.players);
	create_processes(&info);

//	unsigned int *ptr;
//	ptr = (unsigned int *)(info.arena);
//	printf("%d %d %d %d\n", *(info.arena), *(info.arena + 1), *(info.arena + 2), *(info.arena + 3));
//	printf("result %u\n", *ptr);
	//gladiatorial_fight(&info);
   // printf("%d", info.count_cycles);
	//print_arena(info.arena);
	if (info.dump >= 0)
	{
		while (info.count_cycles <= info.dump) // temporary
			gladiatorial_fight(&info, &sdl);
		print_arena(info.arena);
	}
	else
	{
		initialize_visual_arena(&sdl, &info);
		event_handler(&info, &sdl); // loop
	}
    printf("Contestant %d, %s, has won !\n", info.last_live, (info.players)[info.last_live - 1].prog_name);

	TTF_CloseFont(sdl.font); //free memory used by font
	SDL_DestroyWindow(sdl.window);
	TTF_Quit();
	SDL_Quit();
	return (0);
}
