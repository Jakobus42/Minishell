/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsadjina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 19:51:00 by jsadjina          #+#    #+#             */
/*   Updated: 2023/09/19 12:11:10 by jsadjina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	unsigned int	i;
	unsigned int	j;

	j = 0;
	i = 0;
	while (src[i] != '\0')
		i++;
	if (size == 0)
		return (i);
	while (src[j] != '\0' && j < (size - 1))
	{
		dst[j] = src[j];
		j++;
	}
	dst[j] = '\0';
	return (i);
}
/*
#include <stdio.h>
#include <bsd/string.h>

int main(void)
{
	char src[] = "lorem ipsum dolor sit amet";
	char dst[] = "";
	size_t size = 0;
	int result;
	int test;

	result = ft_strlcpy(dst, src, size); 
	printf("result :%d\n", result);
	printf("result2: %s\n", dst);
//	test = strlcpy(dst, src, size);
//	printf("test: %d\n", test);
//	printf("test2: %s\n", dst);

	return(0);
}
*/
