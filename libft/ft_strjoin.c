/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsadjina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 21:01:56 by jsadjina          #+#    #+#             */
/*   Updated: 2023/09/19 12:41:10 by jsadjina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t		i;
	char		*str;

	i = 0;
	if (!s1 && !s2)
		return (NULL);
	if (s1 || s2)
		i = ft_strlen(s1) + ft_strlen(s2);
	str = malloc((i + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[0] = '\0';
	if (s1 && s2)
	{
		ft_strlcpy(str, s1, i + 1);
		ft_strlcat(str, s2, i + 1);
		return (str);
	}
	return (0);
}
/*
#include <stdio.h>
#include <string.h>

int main(void)
{
	char const s1[] = "Hello";
	char const s2[] = "WORLD!";
	char *result;

	result = ft_strjoin(s1, s2);
	printf("result: %s", result);

	return(0);
}
*/
