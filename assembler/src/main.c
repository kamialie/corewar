/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wclayton <wclayton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:33:27 by wclayton          #+#    #+#             */
/*   Updated: 2020/01/30 05:03:56 by wclayton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lc.h"
#include <stdio.h>
#include <errno.h>

int f_lex(int fd)
{
    char *line;
    int res;
    t_nc nc;
    //read comment and name

    get_next_line(fd, &line);
    

    while((res = get_next_line(fd, &line)) > -1)
    {

    }
}

int main(void)
{
    int fd;

    errno = 0;
    if (!(fd = open("src", O_RDONLY)))
    {
        perror("lol");
        return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
    f_lex(fd);
}

//lex and compile asm to bytecode