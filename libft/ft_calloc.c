/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsadjina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 20:09:28 by jsadjina          #+#    #+#             */
/*   Updated: 2023/09/19 12:38:06 by jsadjina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	int	*a;

	a = malloc(nmemb * size);
	if (a == 0)
		return (NULL);
	else
		ft_memset(a, 0, (nmemb * size));
	return (a);
}
/*
#include <string.h>
#include <stdio.h>

int main(void)
{
	size_t	nmemb;
	size_t	size;
	int *d;

	nmemb = 7;
	size = sizeof(unsigned int);

	d = ft_calloc(nmemb, size);
	return(0);
}
*/
