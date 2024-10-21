/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsadjina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 12:03:16 by jsadjina          #+#    #+#             */
/*   Updated: 2023/09/19 12:42:49 by jsadjina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*p;
	char	ch;

	ch = c;
	p = (char *)s;
	i = 0;
	while (p[i] != '\0')
	{
		if (p[i] == ch)
			return (&p[i]);
		i++;
	}
	if (ch == 0)
		return (&p[i]);
	return (NULL);
}
/*
#include <stdio.h>
#include <string.h>

int main(void)
{
	char s[] = "adklawdjkadjakdaldkladkwwaldkada";
	int c = '\0';
	char *result;
	char *test;

	result = ft_strchr(s, c);
	printf("%s\n", result);

	test = strchr(s, c);
	printf("%s", test);
	
	return(0);
}
*/
