/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: max <max@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:33:27 by wclayton          #+#    #+#             */
/*   Updated: 2020/02/11 15:55:56 by max              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lc.h"
#include <string.h>
#include <stdio.h>

unsigned char add_code(unsigned char num)
{
    char out;
    out = num;
    out ^= 0b11111111;
    out += 0b1;
    return (out);
}
int print_bits(unsigned char a)
{
    int i;
    int out;
    int add;
    i = 0;
    out = 0;
    while (i < 8)
    {
        if (a & 0b10000000)
        {
            putchar('1');
            add = 0b10000000;
            add = add >> i;
            out += add;
        }
        else
            putchar('0');
        a = a << 1;
        ++i;   
    }
    return (out);
}

int main(int ac, char **av)
{
    unsigned char num = (unsigned char)atoi(av[1]);
    unsigned short i;
    printf("= %d\n", print_bits(add_code(num)));
    return (EXIT_SUCCESS);
}