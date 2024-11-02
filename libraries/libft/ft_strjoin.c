/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 21:01:56 by jsadjina          #+#    #+#             */
/*   Updated: 2024/11/01 20:34:37 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	char	*str;

	i = 0;
	if (!s1 && !s2)
		return (NULL);
	if (s1 || s2)
		i = ft_strlen(s1) + ft_strlen(s2);
	str = ft_calloc((i + 1), sizeof(char));
	if (!str)
		return (NULL);
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

int	main(void)
{
	char const	s1[] = "Hello";
	char const	s2[] = "WORLD!";
	char		*result;

	result = ft_strjoin(s1, s2);
	printf("result: %s", result);
	return(0);
}
*/
