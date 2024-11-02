/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 14:51:54 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/11/02 14:51:55 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/utils.h"

void	skip_whitespaces(const char **str)
{
	while (**str && ft_strchr(" \t\n\r\v\f", **str))
		(*str)++;
}

char	*ft_strjoin_null(char const *s1, char const *s2)
{
	size_t	i;
	char	*str;

	i = 0;
	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup((char *)s2));
	if (!s2)
		return (ft_strdup((char *)s1));
	if (s1 || s2)
		i = ft_strlen(s1) + ft_strlen(s2);
	str = ft_calloc((i + 1), sizeof(char));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1, i + 1);
	ft_strlcat(str, s2, i + 1);
	return (str);
}
