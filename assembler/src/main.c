/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: max <max@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:33:27 by wclayton          #+#    #+#             */
/*   Updated: 2020/02/10 10:00:43 by max              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lc.h"
#include <stdio.h>
#include <errno.h>

char *strip_arg(char *str)
{
    int i;
    int j;
    int lout;
    int len;
    char *out;
    char *tempstr;

    if (!str)
        return (0);
    i = 0;
    lout = 0;
    len = ft_strlen(str);
    while (i < len)
    {
        if (str[i] != ' ' && str[i] != '\t' && str[i] != '\v' 
            && str[i] != ' ' 
            && str[i] != '\n' && str[i] != '\f' && str[i] != '\r')
            ++lout;
        ++i;
    }
    if (!(out = (char*)malloc(sizeof(char) * lout)))
        return (0);
    ft_bzero(out, lout);
    i = 0;
    j = 0;
    while (i < len)
    {
        if (str[i] != ' ' && str[i] != '\t' && str[i] != '\v' 
            && str[i] != ' ' 
            && str[i] != '\n' && str[i] != '\f' && str[i] != '\r')
        {
            out[j] = str[i];
            ++j;
        }
        ++i;
    }
    return (out);
}

t_op    op_tab[17] =
{
	{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0},
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
		"et (and  r1, r2, r3   r1&r2 -> r3", 1, 0},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
		"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
		"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0},
	{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
		"load index", 1, 1},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
		"store index", 1, 1},
	{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
		"long load index", 1, 1},
	{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1},
	{"aff", 1, {T_REG}, 16, 2, "aff", 1, 0},
	{0, 0, {0}, 0, 0, 0, 0, 0}
};
int is_label(char c)
{
    int i;

    i = 0;
    while (LABEL_CHARS[i])
    {
        if (c == LABEL_CHARS[i])
            return (c);
        
    }
}

t_oper *pushback_oplist(t_oper *oper, t_com com)
{
    t_oper *out;
    
    if(!(out = (t_oper*)malloc(sizeof(t_oper))))
        return (0);
    out->com = com;
    out->next = 0;
    if (oper)
    {
        oper->last->next = out;
        oper->last = oper->last->next;
    }
    else
    {
        out->last = out;
        oper = out;
    }
    return (oper);
}

int arg2int(char *arg)
{

}

int f_lex(int fd)
{
    char *line;
    char **tmpd;
    int res;
    t_nc nc;
    int i,j,k, err;
    unsigned int op;
    char c;
    char *tmpstr;
    int lc;
    //read comment and name
    //add cycling and switch for labels comment and name processing

    get_next_line(fd, &line);
    if (ft_strchr((const char*)line, LABEL_CHAR))
    {
        i = 0;
        //get label
        lc = 0;
        while (line[i] && line[i] != LABEL_CHAR)
        {
            if (!is_label(line[i]))
                err = 1;
        }
        if (line[i] != lc)
            err = 1;
    }
    i = 0;
    op = 0;
    if (!(ft_isalnum(line[i])))
        ++i;
    j = 0;
    while (j < 16)
    {
        if (!ft_strncmp((const char*)(op_tab[j].name),
            (const char*)(line + i),
            ft_strlen((const char*)(op_tab[j].name))))
            op = op_tab[j].code;
        ++j;
    }
    if (op != 0)
        i += ft_strlen(op_tab[op - 1].name);
    else
    {
        

    }
    tmpd = ft_strsplit(line + i, SEPARATOR_CHAR);
    k = 0;

    //check
    while (tmpd[k])
    {
        printf("%s\n", tmpd[k]);
        ++k;
    }
    //check

    //strip args
    k = -1;
    while (++k < 3 && tmpd[k])
    {
        tmpstr = tmpd[k];
        tmpd[k] = strip_arg(tmpd[k]);
        free(tmpstr);
    }
    //stripped
    //array and opcode > digits > t_com
    
    return (1);
}

int main(void)
{
    int fd;

    errno = 0;
    write(1, "started\n", 8);
    if (!(fd = open("test", O_RDONLY)))
    {
        perror("lol");
        return (EXIT_FAILURE);
    }
    else
    {
        f_lex(fd);
    }
    
    return (EXIT_SUCCESS);
    
}

//lex and compile asm to bytecode