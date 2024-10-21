/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsadjina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 14:41:29 by jsadjina          #+#    #+#             */
/*   Updated: 2023/09/19 12:13:51 by jsadjina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	if (i != n)
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	return (0);
}
/*
#include <string.h>
#include <stdio.h>

int main(void)
{
	char s1[] = "testadawdada";
	char s2[] = "testawwdadwawd";
	unsigned int n;
	int result;
	int test;

	n = 6;

	result = ft_strncmp(s1, s2, n);
	printf("%i\n", result);
	test = strncmp(s1, s2, n);
	printf("%i", test);

	return (0);
}
*/
