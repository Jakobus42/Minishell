/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsadjina <jsadjina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 14:35:46 by jsadjina          #+#    #+#             */
/*   Updated: 2023/12/10 15:41:27 by jsadjina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

int		gnl_ft_strchr(char const *s1, int c);
char	*gnl_ft_strjoin(char *s1, char *s2);
char	*get_next_line(int fd, int flag);
char	*gnl_ft_strdup(const char *s);
size_t	gnl_ft_strlen(char *s);

#endif
