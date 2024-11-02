/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 20:09:28 by jsadjina          #+#    #+#             */
/*   Updated: 2024/11/01 20:32:35 by lbaumeis         ###   ########.fr       */
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
#include <stdio.h>
#include <string.h>

int	main(void)
{
	size_t	nmemb;
	size_t	size;
	int		*d;

	nmemb = 7;
	size = sizeof(unsigned int);
	d = ft_calloc(nmemb, size);
	return(0);
}
*/
