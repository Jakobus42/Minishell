/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsadjina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 14:26:45 by jsadjina          #+#    #+#             */
/*   Updated: 2023/10/17 15:31:57 by jsadjina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*gnl_ft_strdup(const char *s)
{
	int		i;
	int		j;
	char	*copy;

	i = 0;
	j = 0;
	while (s[j] != '\0')
		j++;
	copy = malloc(sizeof(char) * j + 1);
	if (!copy)
		return (0);
	while (i < j)
	{
		copy[i] = s[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

int	gnl_ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != c && s[i] != '\0')
		i++;
	if (s[i] == c)
		return (1);
	else
		return (0);
}

static size_t	gnl_ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t			i;
	size_t			j;
	size_t			k;
	unsigned char	*r;
	size_t			x;

	r = (unsigned char *) src;
	j = 0;
	i = 0;
	k = 0;
	while (dst[i] != '\0')
		i++;
	while (r[j] != '\0')
		j++;
	if (i >= size || size == 0)
		return (j + size);
	x = i;
	while (r[k] != '\0' && k < (size - x - 1))
	{
		dst[i] = r[k];
		k++;
		i++;
	}
	dst[i] = '\0';
	return (j + x);
}

size_t	gnl_ft_strlen(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*gnl_ft_strjoin(char *s1, char *s2)
{
	size_t		i;
	char		*str;
	size_t		j;

	if (!s1)
		return (gnl_ft_strdup(s2));
	j = 0;
	i = gnl_ft_strlen(s1) + gnl_ft_strlen(s2);
	str = malloc((i + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (s1[j] != '\0')
	{
		str[j] = s1[j];
		j++;
	}
	str[j] = '\0';
	gnl_ft_strlcat (str, s2, (i + 1));
	return (str);
}
