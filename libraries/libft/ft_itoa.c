/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsadjina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 13:00:13 by jsadjina          #+#    #+#             */
/*   Updated: 2023/09/21 13:59:27 by jsadjina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count(int n)
{
	int	count;

	count = 0;
	if (n <= 0)
		count = 1;
	while (n)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

static char	*intmin(int n)
{
	char	*str;

	str = NULL;
	if (n == -2147483648)
	{
		str = malloc(12 * sizeof(char));
		if (!str)
			return (NULL);
		ft_strlcpy(str, "-2147483648", 12);
	}
	return (str);
}

char	*ft_itoa(int n)
{
	int		len;
	char	*str;

	len = ft_count(n);
	if (n == -2147483648)
		return (intmin(n));
	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (n < 0)
	{
		str[0] = '-';
		n = -n;
	}
	if (n == 0)
		str[0] = '0';
	while (n)
	{
		str[len - 1] = n % 10 + 48;
		len--;
		n = n / 10;
	}
	return (str);
}
/*
#include <stdio.h>
#include <string.h>

int main(void)
{
	char *result;
	int n;

	n = -2147483648;
	result = ft_itoa(n);
	printf("%s", result);

	return(0);
}
*/
