/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsadjina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 11:47:30 by jsadjina          #+#    #+#             */
/*   Updated: 2023/09/19 12:07:15 by jsadjina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" 

int	ft_atoi(const char *nptr)
{
	int	i;
	int	j;
	int	nb;

	i = 0;
	j = 1;
	nb = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '-')
	{
		j = -1;
		i++;
	}
	else if (nptr[i] == '+')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		nb = 10 * nb;
		nb = nptr[i] - 48 + nb;
		i++;
	}
	return (nb * j);
}
/*
#include <stdio.h>

int main(void)
{
	char nptr[] = " +121123131  -123131 121211";
	printf("%d\n", ft_atoi(nptr));
	printf("%d", atoi(nptr));

	return(0);
}
*/
