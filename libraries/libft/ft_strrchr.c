/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsadjina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 14:10:55 by jsadjina          #+#    #+#             */
/*   Updated: 2023/09/19 12:43:17 by jsadjina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*p;
	char	ch;

	ch = c;
	p = (char *)s;
	i = 0;
	while (p[i] != '\0')
		i++;
	if (p == 0)
		return (p);
	while (i >= 0)
	{
		if (p[i] == ch)
			return (&p[i]);
		i--;
	}
	if (ch == 0)
		return (&p[i]);
	return (0);
}
/*
#include <stdio.h>
#include <string.h>

int main(void)
{
	char s[] = "";
	int c = 'c';
	char *result;
	char *test;

//	result = ft_strrchr(s, c);
//	printf("%s\n", result);

	test = strrchr(s, c);
	printf("%s", test);
	
	return(0);
}
*/
