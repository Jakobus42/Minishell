/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unsigned_int_fd.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 15:14:10 by jsadjina          #+#    #+#             */
/*   Updated: 2024/11/02 12:51:36 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_fd.h"

static int	ft_upper_or_lower(int c)
{
	int	diff;

	diff = 87;
	if (c == 'X')
		diff = 55;
	return (diff);
}

static void	ft_calc_fd(unsigned int nber, int i, int c, int divider)
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
		write(2, &str[i], 1);
}

int	ft_print_unsigned_int_fd(int fd, unsigned int nber, char c)
{
	int				i;
	int				i_nber;
	unsigned int	n;
	int				divider;

	(void)fd;
	divider = 10;
	i = 1;
	n = nber;
	if (c == 'x' || c == 'X')
		divider = 16;
	if (nber == 0)
	{
		write(fd, "0", 1);
		return (1);
	}
	while (nber > ((unsigned int)divider - 1))
	{
		nber = nber / divider;
		i++;
	}
	i_nber = i;
	ft_calc_fd(n, i, c, divider);
	return (i_nber);
}
/*
#include <stdio.h>

int	main(void)
{
	unsigned int	a;
	char			b;

	a = -124365;
	b = 'x';
	printf ("\n{%d}", ft_print_unsigned_int(a, b));
	printf ("%x", a);
	return (0);
}
*/
