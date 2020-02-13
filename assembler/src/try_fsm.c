/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_fsm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: max <max@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:33:27 by wclayton          #+#    #+#             */
/*   Updated: 2020/02/13 17:08:06 by max              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lc.h"

typedef enum states {
    INITIAL,
    LABEL_OR_OP,
    LABEL,
    OP,
    COMMENT,
    PROGNAME_OR_PROGCOM,
    TOKEN_STR_1,
    TOKEN_STR_2,
    LIVE,
    LD,
    ST,
    ADD,
    SUB,
    AND,
    OR,
    XOR,
    ZJMP,
    LDI,
    STI,
    FORK,
    LLD,
    LLDI,
    LFORK,
    AFF,
    ERR,
    ARG1,
    ARG2,
    ARG3,
    ARG1DIRLAB,
    ARG1INDLAB,
    ARG1REG,
    ARG1IND,
    ARG1DIR,
    ARG2DIRLAB,
    ARG2INDLAB,
    ARG2REG,
    ARG2IND,
    ARG2DIR,
    ARG3DIRLAB,
    ARG3INDLAB,
    ARG3REG,
    ARG3IND,
    ARG3DIR,
    ZER
};

enum states morphTable[43][13] = 
{
    
}

void iterate()

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