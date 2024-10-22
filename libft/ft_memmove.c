/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsadjina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 19:07:17 by jsadjina          #+#    #+#             */
/*   Updated: 2023/09/19 12:10:09 by jsadjina         ###   ########.fr       */
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
#include <string.h>
#include <stdio.h>

int main(void)
{
	char src = ((void*)0);
	char dest = ((void*)0);
	size_t n = 5;

	ft_memmove(dest, src, n);
	printf("result: %s\n", dest);

	memmove(dest, src, n);
	printf("test: %s\n", dest);

	return(0);
}
*/
