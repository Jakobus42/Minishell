/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 20:10:19 by jsadjina          #+#    #+#             */
/*   Updated: 2024/11/01 20:33:05 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;
	char	*str;

	i = 0;
	str = (char *)s;
	while (i < n)
	{
		if (str[i] == (char)c)
			return (&str[i]);
		i++;
	}
	return (NULL);
}
/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char	j[] = "YOYOYOYodadad";
	int		k;
	size_t	y;
	char	*a;

	k = 'O';
	y = 10;
//	char	*d;
//	d = ft_memchr(j, k, y);
//	printf("%s", d);
	a = memchr(j, k, y);
	printf("%s", a);
	return(0);
}
*/
