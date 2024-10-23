/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsadjina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 18:30:49 by jsadjina          #+#    #+#             */
/*   Updated: 2023/09/19 12:12:20 by jsadjina         ###   ########.fr       */
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

int main(void)
{
	char const s[] = "hola";
	unsigned int start = 5;
	unsigned len = 2;
	char *result;

	result = ft_substr(s, start, len);
	printf("result: %s", result);

	return(0);
}
*/
