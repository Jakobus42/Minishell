/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_length.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 16:27:59 by jsadjina          #+#    #+#             */
/*   Updated: 2024/11/01 20:33:02 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_print_nbr(int number)
{
	number = number + 48;
	write(1, &number, 1);
}

static void	ft_put_nbr(int nb)
{
	if (nb == -2147483648)
	{
		write(1, "-2147483648", 11);
		return ;
	}
	if (nb < 0)
	{
		write(1, "-", 1);
		ft_put_nbr(-nb);
		return ;
	}
	if (nb > 9)
	{
		ft_put_nbr(nb / 10);
		ft_put_nbr(nb % 10);
	}
	else
		ft_print_nbr(nb);
}

int	ft_length(int nb)
{
	int	i;

	i = 1;
	ft_put_nbr(nb);
	if (nb == -2147483648)
		return (11);
	if (nb < 0)
	{
		i++;
		nb *= -1;
	}
	while (nb > 9)
	{
		i++;
		nb /= 10;
	}
	return (i);
}

/*
#include <stdio.h>

int	main(void)
{
	int	number;
	int	result;

	number = -2147483648;
	result = ft_length(number);
	printf(" %d", result);
	return(0);
}
*/
