/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 18:30:49 by jsadjina          #+#    #+#             */
/*   Updated: 2024/11/01 20:35:20 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	int		i;
	char	*substr;
	int		j;

	i = start;
	j = 0;
	if (ft_strlen(s) < start)
		return (ft_strdup(""));
	else if (len > (ft_strlen(s) - start))
		len = ft_strlen(s) - start;
	substr = malloc((len + 1) * sizeof(char));
	if (!substr)
		return (NULL);
	while (s[i] != '\0' && len > 0)
	{
		substr[j] = s[i];
		i++;
		len--;
		j++;
	}
	substr[j] = '\0';
	return (substr);
}
/*
#include <stdio.h>

int	main(void)
{
	char const		s[] = "hola";
	unsigned int	start;
	unsigned		len;
	char			*result;

	start = 5;
	len = 2;
	result = ft_substr(s, start, len);
	printf("result: %s", result);
	return(0);
}
*/
