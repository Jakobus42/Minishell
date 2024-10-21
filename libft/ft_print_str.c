/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsadjina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 13:35:46 by jsadjina          #+#    #+#             */
/*   Updated: 2023/09/29 13:58:22 by jsadjina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_str(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (write(1, "(null)", 6));
	while (str[i] != '\0')
	{
		write(1, &str[i], 1);
		i++;
	}
	return (i);
}
/*
#include <stdio.h>
int main(void)
{
	char *str = NULL;
	int	 result;
	int  result2;

	result = ft_print_str(str);
	result2 = printf("%s\n", str);
	printf("own: %d ///// real: %d", result, result2);
	printf("\n\n\n\n NULL %s NULL ", NULL);

	return(0);
}
*/
