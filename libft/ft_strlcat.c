/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsadjina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 11:54:18 by jsadjina          #+#    #+#             */
/*   Updated: 2023/09/07 20:25:52 by jsadjina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	k;
	unsigned char	*r;
	unsigned int	x;

	r = (unsigned char *) src;
	j = 0;
	i = 0;
	k = 0;
	while (dst[i] != '\0')
		i++;
	while (r[j] != '\0')
		j++;
	if (i >= size || size == 0)
		return (j + size);
	x = i;
	while (r[k] != '\0' && k < (size - x - 1))
	{
		dst[i] = r[k];
		k++;
		i++;
	}
	dst[i] = '\0';
	return (j + x);
}
/*
#include <stdio.h>
#include <bsd/string.h>

int main(void)
{
	char src[] = "Wie soll das gehn?";
	char dst[] = "na ganz einfach!";
	size_t size = 27;
	int result;
//	int test;

	result = ft_strlcat(dst, src, size);
	printf("result: %d\n", result);
//	test = strlcat(dst, src, size);
//	printf("test: %d\n", test);
	printf("dest: %s", dst);

	return(0);
}
*/
