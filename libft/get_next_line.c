/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsadjina <jsadjina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 14:59:35 by jsadjina          #+#    #+#             */
/*   Updated: 2023/12/15 15:39:48 by jsadjina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

static char	*tacticle_free(char *stash, char *buffer)
{
	char	*joined;

	joined = gnl_ft_strjoin(stash, buffer);
	if (stash)
	{
		free(stash);
		stash = NULL;
	}
	return (joined);
}

static char	*ft_clear_stash(char *stash, unsigned int i)
{
	char			*temp;
	unsigned int	j;

	j = 0;
	if (!stash)
		return (NULL);
	if (stash[i] == '\n')
		i++;
	while (stash[i + j] != '\0')
		j++;
	temp = (char *)malloc((j + 1) * sizeof(char));
	if (!temp)
	{
		free(stash);
		return (NULL);
	}
	temp[j] = '\0';
	while (j--)
		temp[j] = stash[i + j];
	free(stash);
	stash = NULL;
	return (temp);
}

static char	*ft_new_line(char *stash)
{
	char			*new_line;
	unsigned int	i;

	i = 0;
	if (!stash)
		return (NULL);
	if (stash[0] == '\0')
		return (NULL);
	while (stash[i] != '\n' && stash[i] != '\0')
		i++;
	if (stash[i] == '\n')
		i++;
	new_line = (char *)malloc((i + 1) * sizeof(char));
	if (!new_line)
		return (NULL);
	new_line[i] = '\0';
	while (i--)
		new_line[i] = stash[i];
	return (new_line);
}

static char	*ft_read(int fd, char *stash)
{
	char	*buffer;
	int		bytes_read;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
	{
		if (stash)
			free(stash);
		return (NULL);
	}
	bytes_read = 1;
	while (gnl_ft_strchr(stash, '\n') == 0 && bytes_read != 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(stash), (stash = NULL), free(buffer), NULL);
		buffer[bytes_read] = '\0';
		stash = tacticle_free(stash, buffer);
		if (!stash)
			break ;
	}
	free(buffer);
	buffer = NULL;
	return (stash);
}

char	*get_next_line(int fd, int flag)
{
	static char		*stash;
	char			*new_line;
	unsigned int	i;

	i = 0;
	if (flag == 1)
		return (free(stash), (stash = NULL), NULL);
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	stash = ft_read(fd, stash);
	if (!stash)
		return (NULL);
	new_line = ft_new_line(stash);
	if (!new_line)
		return (free(stash), (stash = NULL), NULL);
	while (stash[i] != '\0' && stash[i] != '\n')
		i++;
	stash = ft_clear_stash(stash, i);
	if (!stash)
	{
		free(new_line);
		return (NULL);
	}
	return (new_line);
}

// #include <stdio.h>

//  int main(void)
//  {
// 	int fd;
// 	char *result;

// 	fd = open("test.txt", O_RDONLY);
// 		if(!fd)
// 			return(0);

// 	while(1)
// 	{
// 		result = get_next_line(0, 0);
// 		if(!result)
// 			break ;
// 		else
// 			free(result);
// 	}
// 	close(fd);

// 	return(0);
//  }
