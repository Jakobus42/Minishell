/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsadjina <jsadjina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 13:06:09 by jsadjina          #+#    #+#             */
/*   Updated: 2024/02/27 18:40:33 by jsadjina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <limits.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

char    *ft_strldup(int start, int limiter, char *str);
int     ft_strpos(char *str, char limiter);
int		ft_atoi(const char *nptr);
long	ft_atol(const char *nptr);
int		ft_isalnum(int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_isascii(int c);
int		ft_isdigit(long c);
int		ft_isprint(int c);
void	*ft_memchr(const void *s, int c, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
char	*ft_strchr(const char *str, int c);
char	*ft_strdup(const char *s);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlen(const char *s);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strrchr(const char *s, int c);
char	*ft_strtrim(char const *s1, char const *set);
int		ft_tolower(int c);
int		ft_toupper(int c);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_memset(void *s, int c, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_putchar_fd(char c, int fd);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
int		ft_isalpha(int c);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strjoin2(char *s1, char *s2);
int     ft_array_size(char **array);
void    ft_print_array(char **array);
int	ft_strcmp2(const char *s1, const char *s2);

#endif
