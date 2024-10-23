/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsadjina <jsadjina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 13:37:24 by jsadjina          #+#    #+#             */
/*   Updated: 2023/12/07 17:36:50 by jsadjina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*p;

	if (!s)
		return (NULL);
	p = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		p[i] = (unsigned char)c;
		i++;
	}
	return (s);
}
/*
#include <stdio.h>
#include <string.h>


int	main(void)
{
	char	s[] = "I like Pizza";
	int		c;
	size_t	n;

	c = '*';
	n = 6;
	printf("%s", (unsigned char *)ft_memset(str, c, n));
	return(0);
}
*/
