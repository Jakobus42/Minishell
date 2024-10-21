/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unsigned_int.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsadjina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 15:14:10 by jsadjina          #+#    #+#             */
/*   Updated: 2023/09/29 15:54:33 by jsadjina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_upper_or_lower(int c)
{
	int	diff;

	diff = 87;
	if (c == 'X')
		diff = 55;
	return (diff);
}

static void	ft_calc(unsigned int nber, int i, int c, int divider)
{
	char	str[12];
	int		a;
	int		diff;

	str[i] = '\0';
	a = i;
	diff = ft_upper_or_lower(c);
	while (i - 1 >= 0)
	{
		str[i - 1] = nber % divider;
		nber /= divider;
		i--;
	}
	while (i < a)
	{
		if (str[i] >= 10 && str[i] <= 15)
			str[i] += diff;
		else
			str[i] += 48;
		i++;
	}
	i = -1;
	while (str[++i])
		write (1, &str[i], 1);
}

int	ft_print_unsigned_int(unsigned int nber, char c)
{
	int				i;
	int				i_nber;
	unsigned int	n;
	int				divider;

	divider = 10;
	i = 1;
	n = nber;
	if (c == 'x' || c == 'X')
		divider = 16;
	if (nber == 0)
	{
		write (1, "0", 1);
		return (1);
	}
	while (nber > ((unsigned int)divider - 1))
	{
		nber = nber / divider;
		i++;
	}
	i_nber = i;
	ft_calc(n, i, c, divider);
	return (i_nber);
}
/*
#include <stdio.h>
int main(void)
{
	unsigned int a = -124365;
	char b = 'x';

	printf ("\n{%d}", ft_print_unsigned_int(a, b));
	printf ("%x", a);
	return (0);
}
*/
