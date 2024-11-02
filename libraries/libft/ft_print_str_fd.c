/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 13:35:46 by jsadjina          #+#    #+#             */
/*   Updated: 2024/11/01 20:33:33 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_fd.h"

int	ft_print_str_fd(int fd, const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (write(fd, "(null)", 6));
	while (str[i] != '\0')
	{
		write(fd, &str[i], 1);
		i++;
	}
	return (i);
}
/*
#include <stdio.h>

int	main(void)
{
	char	*str;
	int		result;
	int		result2;

	str = NULL;
	result = ft_print_str(str);
	result2 = printf("%s\n", str);
	printf("own: %d ///// real: %d", result, result2);
	printf("\n\n\n\n NULL %s NULL ", NULL);
	return(0);
}
*/
