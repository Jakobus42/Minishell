/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 16:51:24 by jsadjina          #+#    #+#             */
/*   Updated: 2024/11/01 20:32:32 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*p;

	p = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		p[i] = '\0';
		i++;
	}
}
/*
#include <stdio.h>
#include <strings.h>

int	main(void)
{
	unsigned char	s[] = "I like Pizza";
	size_t			n;

	n = 6;
	ft_bzero(s, n);
	printf(" result: %s", s);
	bzero(s, n);
	printf(" test: %s\n", s);
	return(0);
}
*/
