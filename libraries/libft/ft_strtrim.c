/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsadjina <jsadjina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 13:01:05 by jsadjina          #+#    #+#             */
/*   Updated: 2023/12/09 18:24:20 by jsadjina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	str_start(char *str1, char const *set)
{
	int	str_len;
	int	start;

	start = 0;
	str_len = ft_strlen(str1);
	while (start < str_len)
	{
		if (ft_strchr(set, str1[start]) == NULL)
			break ;
		start++;
	}
	return (start);
}

static int	str_end(char *str1, char const *set)
{
	int	end;
	int	i;

	end = ft_strlen(str1);
	i = 0;
	while (i < end)
	{
		if (ft_strchr(set, str1[end - i - 1]) == NULL)
			break ;
		i++;
	}
	return (end - i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str1;
	char	*trim_str;
	size_t	start;
	size_t	end;

	str1 = (char *)s1;
	if (str1 == NULL)
		return (0);
	if (set == NULL)
		return (0);
	start = str_start(str1, set);
	end = str_end(str1, set);
	if (start >= end)
		return (ft_strdup(""));
	trim_str = malloc(sizeof(char) * (end - start) + 1);
	if (!trim_str)
		return (NULL);
	ft_strlcpy (trim_str, str1 + start, end - start + 1);
	return (trim_str);
}
/*
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	char *result;
	char s1[] = "        ";
	char set[] = "a";

	result = ft_strtrim(s1, set);
	printf("%s", result);

	return (0);
}
*/
