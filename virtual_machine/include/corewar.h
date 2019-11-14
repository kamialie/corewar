/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 15:10:22 by rgyles            #+#    #+#             */
/*   Updated: 2019/11/14 20:05:59 by bdudley          ###   ########.fr       */
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

typedef struct	s_op
{
	char					*name;
	unsigned int			args_num : 2;
	unsigned char			args_types[3];
	unsigned int			code : 5;
	unsigned int			cycle_for_exec : 11;
	char					*comment;
	unsigned int			change_carry : 1;
	unsigned int			args_types_code : 1;
	unsigned char			t_dir_size : 3;
}				t_op;

# include <stdio.h>

// END

void		print_arena(unsigned char *arena);

void		read_arg(t_info *info, int argc, char *argv[]);
void		create_processes(t_info *info);
void		delete_elem(t_processes **processes, t_info *info);
void		gladiatorial_fight(t_info *info);

void		error(int err);

static t_op	g_op_tab[16] =
		{
				{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0, 4},
				{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 1, 4},
				{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 1, 4},
				{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 1, 4},
				{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 1, 4},
				{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
						"et (and  r1, r2, r3   r1&r2 -> r3", 1, 1, 4},
				{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
						"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 1, 4},
				{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
						"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 1, 4},
				{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 0, 2},
				{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
						"load index", 1, 1, 2},
				{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
						"store index", 1, 1, 2},
				{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 0, 2},
				{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 1, 4},
				{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
						"long load index", 1, 1, 2},
				{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 0, 2},
				{"aff", 1, {T_REG}, 16, 2, "aff", 1, 1, 4}
		};

#endif
