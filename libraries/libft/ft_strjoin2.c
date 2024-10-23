/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsadjina <jsadjina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 16:54:24 by jsadjina          #+#    #+#             */
/*   Updated: 2023/11/26 16:54:57 by jsadjina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin2(char *s1, char *s2)
{
	size_t	i;
	char	*str;

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
	free(s1);
	return (0);
}
