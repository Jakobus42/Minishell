/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 18:30:13 by jsadjina          #+#    #+#             */
/*   Updated: 2024/11/01 20:33:11 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*final_dest;

	i = 0;
	final_dest = dest;
	if (!src && !dest)
		return (0);
	while (i < n)
	{
		*final_dest = *(unsigned char *)src;
		final_dest++;
		i++;
		src++;
	}
	return (final_dest - n);
}
/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char			src[] = "";
	char			dest[] = "";
	size_t			n;
	unsigned char	*result;
	unsigned char	*test;

	n = 10;
//	result = ft_memcpy(dest, src, n);
//	printf("result: %s\n", result);
	test = memcpy(dest, src, n);
	printf("test: %s\n", test);
	return(0);
}
*/
