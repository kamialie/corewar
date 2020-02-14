/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_fsm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wclayton <wclayton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:33:27 by wclayton          #+#    #+#             */
/*   Updated: 2020/02/14 21:37:04 by wclayton         ###   ########.fr       */
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

//wrapper
char *readf(int fd)
{
    char *buf;
    char *out;
    char *tmp;

    while (read(fd, buf, 1000))
    {
        tmp = out;
        if (!(out = ft_strjoin(out, buf)))
            return (0);
        if (tmp)
            free(tmp);
    }  
    return (out);
}

t_oper  *FSM(char *buf)
{
    if (*buf == LABEL_CHAR)
        ;
    if (*buf == COMMENT_CHAR)
        ;
    if (*buf == DIRECT_CHAR)
        ;
    if (*buf == LABEL_CHAR)
        ;
    if (*buf == SEPARATOR_CHAR)
        ;
    if (*buf == '.')
        ;
    if (*buf == ' ')
        ;
    if (ft_isalnum(*buf))
        ;
    if (*buf == '\0')
        ;
    if (*buf == COMMENT_CHAR)
        ;
    if (*buf == COMMENT_CHAR)
        ;
    if (*buf == COMMENT_CHAR)
        ;
    if (*buf == COMMENT_CHAR)
        ;
}

int parse_inp(int fd)
{
    char *buf;
    t_oper *opchain;
        
    if (!(buf = readf(fd)) || !(opchain = (t_oper*)malloc(sizeof(opchain))))
        return (0);
    opchain = FSM(buf);
}

int main(void)
{
    int fd;
    
    if (!(fd = open("test", O_RDONLY)) || !parse_inp(fd))
        return (EXIT_FAILURE);
    else
        return (EXIT_SUCCESS);
    



}