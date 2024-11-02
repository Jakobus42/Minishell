/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 14:50:56 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/11/02 15:01:17 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/expander/expander.h"
#include "core/parser/parser.h"
#include "core/shell/shell.h"
#include "core/shell/signal.h"
#include "utils/logger.h"
#include <fcntl.h>

static int	generate_random_string(char *buf, const size_t len, const char *set)
{
	size_t	i;
	ssize_t	bytes_read;
	size_t	charset_size;
	int		fd;

	i = 0;
	fd = open("/dev/urandom", O_RDONLY);
	if (fd == -1)
		return (log_message(LOG_ERROR, "/dev/urandom: %s", strerror(errno)),
			-1);
	bytes_read = read(fd, buf, len);
	close(fd);
	if (bytes_read != (ssize_t)len)
		return (log_message(LOG_ERROR, "Failed to read %zu bytes: %s\n", len,
				strerror(errno)), -1);
	charset_size = ft_strlen(set);
	while (i < len)
	{
		buf[i] = set[buf[i] % charset_size];
		i++;
	}
	buf[len] = '\0';
	return (0);
}

static char	*generate_unique_filename(t_shell *shell)
{
	char		*filename;
	const char	set[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTU12345";

	filename = ft_calloc(HEREDOC_FILENAME_LENGTH + 1, sizeof(char));
	if (!filename)
		error_fatal(shell, "ft_calloc in generate_unique_filename",
			MALLOC_FAIL);
	if (generate_random_string(filename, HEREDOC_FILENAME_LENGTH, set) == -1)
		return (free(filename), NULL);
	return (filename);
}

static void	read_input(t_shell *shell, char *eof, const int fd)
{
	char	*input;
	char	*expanded;
	char	*eof_no_quotes;
	bool	should_expand;

	should_expand = (!ft_strchr(eof, '\'') && !ft_strchr(eof, '\"'));
	eof_no_quotes = remove_quotes(eof);
	while (true)
	{
		input = readline("> ");
		if (!input)
			return (log_message(LOG_ERROR, "warning: heredoc delimited by "
					"end-of-file(wanted `%s')\n", eof_no_quotes), free(input));
		if (!ft_strcmp(eof_no_quotes, input) || g_signal == SIGINT)
			break ;
		if (should_expand)
		{
			expanded = expand_token(shell, input, false);
			free(input);
			input = expanded;
		}
		ft_putendl_fd(input, fd);
		free(input);
	}
	free(input);
}

static char	*read_into_heredoc(t_shell *shell, char *eof)
{
	char	*filename;
	int		fd;

	filename = generate_unique_filename(shell);
	if (!filename)
		return (NULL);
	fd = open(filename, O_WRONLY | O_CREAT, 777);
	if (fd == -1)
	{
		free(filename);
		log_message(LOG_ERROR, "cant create here document: %s\n",
			strerror(errno));
		return (NULL);
	}
	read_input(shell, eof, fd);
	close(fd);
	if (errno == ENOMEM)
		error_fatal(shell, "readline malloc failure", MALLOC_FAIL);
	return (filename);
}

void	open_heredocs(t_shell *shell, t_list *tokens)
{
	t_token_type	prv_token_type;
	char			*ptr;
	t_token			*token;

	prv_token_type = NONE;
	ptr = NULL;
	handle_signal(shell, MODE_HEREDOC);
	while (tokens)
	{
		token = (t_token *)tokens->content;
		if (prv_token_type == HEREDOC && token->type == WORD)
		{
			ptr = token->value;
			token->value = read_into_heredoc(shell, token->value);
			free(ptr);
		}
		prv_token_type = token->type;
		tokens = tokens->next;
	}
	handle_signal(shell, MODE_NON_INTERACTIVE);
}
