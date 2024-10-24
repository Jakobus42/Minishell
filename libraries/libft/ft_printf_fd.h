/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsadjina <jsadjina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 15:25:07 by jsadjina          #+#    #+#             */
/*   Updated: 2023/12/11 22:26:08 by jsadjina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_FD__H
# define FT_PRINTF_FD_H
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

int	ft_printf_fd(int fd, const char *format, ...);
int	ft_length_fd(int fd, int nb);
int	ft_print_ptr_fd(int fd, void *nber);
int	ft_print_str_fd(int fd, const char *str);
int	ft_print_unsigned_int_fd(int fd, unsigned int nber, char c);

#endif
