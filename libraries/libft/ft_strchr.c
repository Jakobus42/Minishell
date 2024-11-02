/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 12:03:16 by jsadjina          #+#    #+#             */
/*   Updated: 2024/11/01 20:34:20 by lbaumeis         ###   ########.fr       */
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

int	main(void)
{
	char	s[] = "adklawdjkadjakdaldkladkwwaldkada";
	int		c;
	char	*result;
	char	*test;

	c = '\0';
	result = ft_strchr(s, c);
	printf("%s\n", result);
	test = strchr(s, c);
	printf("%s", test);
	return(0);
}
*/
