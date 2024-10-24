#include "ft_printf_fd.h"

static int	ft_print_char_fd(int fd, int c)
{
	write(fd, &c, 1);
	return (1);
}

static int	ft_formats_fd(int fd, va_list args, const char format)
{
	int	length;

	length = 0;
	if (format == 'c')
		length += ft_print_char_fd(fd, va_arg(args, int));
	else if (format == 's')
		length += ft_print_str_fd(fd, va_arg(args, const char *));
	else if (format == 'p')
		length += ft_print_ptr_fd(fd, va_arg(args, void *));
	else if (format == 'd')
		length += ft_length_fd(fd, va_arg(args, int));
	else if (format == 'i')
		length += ft_length_fd(fd, va_arg(args, int));
	else if (format == 'u')
		length += ft_print_unsigned_int_fd(fd, va_arg(args, unsigned int), format);
	else if (format == 'x')
		length += ft_print_unsigned_int_fd(fd, va_arg(args, unsigned int), format);
	else if (format == 'X')
		length += ft_print_unsigned_int_fd(fd, va_arg(args, unsigned int), format);
	else if (format == '%')
		length += ft_print_char_fd(fd, '%');
	return (length);
}

int	ft_printf_fd(int fd, const char *format, ...)
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
			length += ft_formats_fd(fd, args, format[i + 1]);
			i++;
		}
		else
			length += ft_print_char_fd(fd, format[i]);
		i++;
	}
	va_end(args);
	return (length);
}