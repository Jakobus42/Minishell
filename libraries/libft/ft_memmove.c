/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 19:07:17 by jsadjina          #+#    #+#             */
/*   Updated: 2024/11/01 20:33:14 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*p;
	unsigned char	*a;

	p = (unsigned char *)src;
	a = (unsigned char *)dest;
	if (!a && !p)
		return (0);
	if (p < a)
	{
		while (n--)
		{
			a[n] = p[n];
		}
	}
	else
	{
		while (n > 0)
		{
			*a++ = *p++;
			n--;
		}
	}
	return (dest);
}
/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char	src;
	char	dest;
	size_t	n;

	src = ((void*)0);
	dest = ((void*)0);
	n = 5;
	ft_memmove(dest, src, n);
	printf("result: %s\n", dest);
	memmove(dest, src, n);
	printf("test: %s\n", dest);
	return(0);
}
*/
