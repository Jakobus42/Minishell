/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 16:36:49 by jsadjina          #+#    #+#             */
/*   Updated: 2024/11/01 20:35:06 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	len_little;
	char	*new_big;
	char	*new_little;

	if (little[0] == 0)
		return ((char *)big);
	new_big = (char *)big;
	new_little = (char *)little;
	len_little = ft_strlen(little);
	if (len_little == 0)
		return (new_big);
	i = 0;
	j = 0;
	while (new_big[i] && (i < len))
	{
		while ((new_big[i + j] == new_little[j]) && new_little[j])
			j++;
		if ((j == len_little) && ((i + j) <= len))
			return (&new_big[i]);
		i++;
		j = 0;
	}
	return (NULL);
}
// #include <stdio.h>
// #include <string.h>
// int	main(void)
// {
// 	char	str[] = "Can you find me?";
// 	char	to_find[] = "find";
// 	char	*result;

// 	result = ft_strnstr(str, to_find, 15);
// 	printf("Own: %s\n", result);

// 	return(0);
// }
