/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_fsm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: max <max@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:33:27 by wclayton          #+#    #+#             */
/*   Updated: 2020/02/12 13:58:14 by max              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lc.h"

typedef enum states {
    INITIAL,
    LC,
    LCS,
    СС,
    CS = 0,
    COMMENT,
    OTH,
    ERR,
    TERM

    


};


int parse_inp(int fd)
{
    char *buf;
    while (read(fd, buf, 1))
    {
        
    }
    
}

int main(void)
{
    int fd;
    
    if (!(fd = open("test", O_RDONLY)) || !parse_inp(fd))
        return (EXIT_FAILURE);
    else
        return (EXIT_SUCCESS);
    



}