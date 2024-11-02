#include "core/expander/expander.h"
#include "core/parser/parser.h"
#include "core/shell/shell.h"
#include "core/shell/signal.h"
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
	while (i++ < len)
	{
		buf[i] = set[buf[i] % charset_size];
		i++;
	}
	buf[len] = '\0';
	return (0);
}

static char	*generate_unique_filename(t_shell *shell)
{
	char	*filename;
	char	set[63];

	set[63] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXY"
		"Z0123456789";
	filename = ft_calloc(HEREDOC_FILENAME_LENGTH + 1, sizeof(char));
	if (!filename)
	{
		error_fatal(shell, "ft_calloc in generate_unique_filename",
			MALLOC_FAIL);
		return (NULL);
	}
	if (generate_random_string(filename, HEREDOC_FILENAME_LENGTH, set) == -1)
		return (free(filename), NULL);
	return (filename);
}

static void	read_input(t_shell *shell, char *eof, const int fd)
{
	char	*input;
	int		i;
	char	*expanded;

	i = 0;
	while (++i)
	{
		input = readline("> ");
		if (!input)
			return (log_message(LOG_ERROR,
					"warning: here-document at line"
					"%d delimited by end-of-file (wanted `%s')\n", i,
					remove_quotes(eof)), free(input));
		if (!ft_strcmp(remove_quotes(eof), input) || g_signal == SIGINT)
			break ;
		if ((!ft_strchr(eof, '\'') && !ft_strchr(eof, '\"')))
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
	char		*filename;
	const int	fd = open(filename, O_WRONLY | O_CREAT);

	filename = generate_unique_filename(shell);
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

	prv_token_type = NULL;
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
