/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 15:10:22 by rgyles            #+#    #+#             */
/*   Updated: 2019/11/12 19:40:02 by bdudley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include "libft.h"
# include "op.h"

# define DUMP "-dump"
# define N "-n"
# define COR ".cor"

//cc - count cycle
typedef struct	s_processes
{
	int					cc_live; //цикл, в котором была последний раз выполнена live
	int					cc_op : 11; //количество циклов, оставшееся до исполнения операции
	int 				carry : 1; //флаг, для некоторых операций
	int					code_op : 5; //код операции
	unsigned char		*ptr; //местоположение каретки на арене
	int 				c_byte_op : 4; //сколько перешагнуть до следущей операции
	char 				reg[REG_NUMBER * REG_SIZE];
	struct s_processes	*next;
	struct s_processes	*prev; //???
}				t_processes;
// TEMPORARY
typedef struct	s_info
{
	int				dump; //количество циклов, на котором требуется напечатать арену
	header_t		players[MAX_PLAYERS]; //массив чемпионов
	unsigned char	*arena;
	t_processes		*processes;
	int 			count_process;
	int 			last_live; //игрок, который последним сказал, что он жив
	int 			count_cycles; //количество циклов прошедших с начала игры
	int				cycle_to_die; //длительность периода проверки
	int 			count_live; //количество выполнынных live за последний период
	int 			count_check; //количество проведенных проверок
}				t_info;

# include <stdio.h>

// END

void		print_arena(unsigned char *arena);

void		read_arg(t_info *info, int argc, char *argv[]);
void		create_processes(t_info info);

void		error(int err);
#endif
