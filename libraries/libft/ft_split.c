/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 12:21:51 by jsadjina          #+#    #+#             */
/*   Updated: 2024/11/02 16:29:37 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	freeall(char **list, int counter)
{
	while (counter >= 0)
	{
		free(list[counter]);
		counter--;
	}
	free(list);
}

static char	**setarray(char const *str, char **list, char c)
{
	size_t	i;
	int		j;

	j = 0;
	while (*str != '\0')
	{
		i = 0;
		while (str[i] != c && str[i] != '\0')
			i++;
		list[j] = ft_substr(str, 0, i);
		if (!list[j])
			return (freeall(list, (j - 1)), NULL);
		str += i;
		while (*str == c && c != '\0')
			str++;
		j++;
	}
	list[j] = NULL;
	return (list);
}

static int	word_count(char const *str, char c)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != c)
		{
			count++;
			while (str[i] != '\0' && str[i] != c)
				i++;
		}
		else
			i++;
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	char	**list;
	int		words;

	if (!s || s[0] == '\0')
		return (NULL);
	while (*s == c && c)
		s++;
	words = word_count(s, c);
	list = (char **)malloc(sizeof(char *) * (words + 1));
	if (!list)
		return (NULL);
	if (words == 0)
	{
		list[0] = NULL;
		return (list);
	}
	list = setarray(s, list, c);
	if (!list)
		return (NULL);
	return (list);
}
/*

#include <stdio.h>

int	main(void)
{
	char	**result;
	int		i;

	result = ft_split("tripouille", 0);
	i = 0;
	while (result[i] != NULL)
	{
		printf("{%s} ", result[i]);
		i++;
	}
	printf("\n");
	i = 0;
	while (result[i] != NULL)
	{
		free(result[i]);
		i++;
	}
	free(result);
	return (0);
}
*/