/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsadjina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 14:29:49 by jsadjina          #+#    #+#             */
/*   Updated: 2023/10/25 18:57:14 by jsadjina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_print_char(int c)
{
	write(1, &c, 1);
	return (1);
}

static int	ft_formats(va_list args, const char format)
{
	int	length;

	length = 0;
	if (format == 'c')
		length += ft_print_char(va_arg(args, int));
	else if (format == 's')
		length += ft_print_str(va_arg(args, const char *));
	else if (format == 'p')
		length += ft_print_ptr(va_arg(args, void *));
	else if (format == 'd')
		length += ft_length(va_arg(args, int));
	else if (format == 'i')
		length += ft_length(va_arg(args, int));
	else if (format == 'u')
		length += ft_print_unsigned_int(va_arg(args, unsigned int), format);
	else if (format == 'x')
		length += ft_print_unsigned_int(va_arg(args, unsigned int), format);
	else if (format == 'X')
		length += ft_print_unsigned_int(va_arg(args, unsigned int), format);
	else if (format == '%')
		length += ft_print_char('%');
	return (length);
}

int	ft_printf(const char *format, ...)
{
	int		i;
	int		length;
	va_list	args;

	i = 0;
	length = 0;
	if (!format)
		return (-1);
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			length += ft_formats(args, format[i + 1]);
			i++;
		}
		else
			length += ft_print_char(format[i]);
		i++;
	}
	va_end(args);
	return (length);
}
/*
#include <stdio.h>

int main(void)
{
	//char *str = NULL;
	//int num;
	//int num2;

	//num = ft_printf("%s\n", str);

	//num2 = printf("%s", str);
	ft_printf("%d", ft_printf(NULL));
	return(0);
}
*/
