/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsadjina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 16:33:17 by jsadjina          #+#    #+#             */
/*   Updated: 2023/09/29 19:13:13 by jsadjina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_fd.h"

static void	ft_calc_fd(int fd, unsigned long long nber, int i)
{
	char	str[16];
	int		a;

	str[i] = '\0';
	a = i;
	while (i - 1 >= 0)
	{
		str[i - 1] = nber % 16;
		nber /= 16;
		i--;
	}
	write(fd, "0x", 2);
	while (i < a)
	{
		if (str[i] >= 10 && str[i] <= 15)
			str[i] += 87;
		else
			str[i] += 48;
		i++;
	}
	i = -1;
	while (str[++i])
		write(fd, &str[i], 1);
}

static int	ft_edge_case_fd(int fd, unsigned long long nb)
{
	if (nb == 0)
		return (write(fd, "(nil)", 5));
	return (0);
}

int	ft_print_ptr_fd(int fd, void *nber)
{
	int						i;
	int						i_nber;
	unsigned long long		n;
	unsigned long long		nb;

	i = 1;
	nb = (unsigned long long)nber;
	if (nb == -nb)
		nb = -nb * -1;
	if (nber == &nber)
		nb = (unsigned long long)&nber;
	n = ft_edge_case_fd(fd, nb);
	if (n != 0)
		return (n);
	n = nb;
	while (nb > 15)
	{
		nb = nb / 16;
		i++;
	}
	i_nber = i;
	ft_calc_fd(fd, n, i);
	return (i_nber + 2);
}
/*
#include <stdio.h>
#include <limits.h>
int main(void)
{
	//void *ptr;
	int result;
	int result2;
	
	result = ft_print_ptr((void *) 1);
	result2 = printf("\n%p", (void *) 1);
	printf("\n%d\n %d", result, result2);
	return (0);
}
*/
