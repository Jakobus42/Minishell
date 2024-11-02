/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 15:25:07 by jsadjina          #+#    #+#             */
/*   Updated: 2024/11/01 20:33:53 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_FD_H
# define FT_PRINTF_FD_H
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

int	ft_printf_fd(int fd, const char *format, ...);
int	ft_vprintf_fd(int fd, const char *format, va_list args);
int	ft_length_fd(int fd, int nb);
int	ft_print_ptr_fd(int fd, void *nber);
int	ft_print_str_fd(int fd, const char *str);
int	ft_print_unsigned_int_fd(int fd, unsigned int nber, char c);

#endif // FT_PRINTF_FD_H