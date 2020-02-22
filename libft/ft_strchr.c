/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 13:46:13 by rgyles            #+#    #+#             */
/*   Updated: 2018/11/30 10:37:04 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char ch;

	ch = (char)c;
	while (*s != '\0')
	{
		if (ch == *s)
			return ((char*)s);
		s++;
	}
	if (ch == '\0')
		return ((char*)s);
	return (NULL);
}
