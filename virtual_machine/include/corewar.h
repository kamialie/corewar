/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 15:10:22 by rgyles            #+#    #+#             */
/*   Updated: 2019/11/08 19:47:13 by bdudley          ###   ########.fr       */
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

// TEMPORARY
typedef struct	s_info
{
	int			dump;
	header_t	players[MAX_PLAYERS];
}				t_info;

# include <stdio.h>

// END

void	init_arena(void);

void	read_arg(t_info *info, int argc, char *argv[]);

void	error(int err);
#endif
