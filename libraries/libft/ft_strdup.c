/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsadjina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 21:02:51 by jsadjina          #+#    #+#             */
/*   Updated: 2023/09/19 12:13:22 by jsadjina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		i;
	int		j;
	char	*copy;

	i = 0;
	j = ft_strlen(s);
	copy = ft_calloc(sizeof(char), j + 1);
	if (!copy)
		return (NULL);
	while (i < j)
	{
		copy[i] = s[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}
/*
#include <string.h>
#include <stdio.h>

int main(void)
{
	char source[] = "I like Pizza";
	char *copy = ft_strdup(source);

	printf("%s", copy);
	return(0);
}
*/
