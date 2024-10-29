#include "core/expander/expander.h"
#include "core/parser/parser.h"
#include "core/shell/shell.h"
#include <fcntl.h>

static int generate_random_string(char *buffer, const size_t length, const char *charset)
{
	size_t i = 0;

	const int fd = open("/dev/urandom", O_RDONLY);
	if (fd == -1)
	{
		log_message(LOG_ERROR, "/dev/urandom: %s", strerror(errno));
		return -1;
	}
	ssize_t bytes_read = read(fd, buffer, length);
	close(fd);
	if (bytes_read != (ssize_t) length)
	{
		log_message(LOG_ERROR, "Failed to read %zu bytes: %s", length, strerror(errno));
		return -1;
	}
	size_t charset_size = strlen(charset);
	while (i < length)
	{
		buffer[i] = charset[buffer[i] % charset_size];
		i++;
	}
	buffer[length] = '\0';
	return 0;
}

static char *generate_unique_filename(t_shell *shell)
{
	const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXY"
	                       "Z0123456789";
	char      *filename;

	filename = ft_calloc(HEREDOC_FILENAME_LENGTH + 1, sizeof(char));
	if (!filename)
	{
		error_fatal(shell, "ft_calloc in generate_unique_filename", MALLOC_FAIL);
		return NULL;
	}
	if (generate_random_string(filename, HEREDOC_FILENAME_LENGTH, charset) == -1)
	{
		free(filename);
		return NULL;
	}
	return filename;
}

static void read_input(t_shell *shell, char *eof, const int fd)
{
	const bool should_expand_input = (!ft_strchr(eof, '\'') && !ft_strchr(eof, '\"'));
	const char *eof_no_quotes = remove_quotes(eof);
	char       *input;

	while ((input = readline("> ")))
	{
		if (!ft_strcmp(eof_no_quotes, input))
			break;
		if (should_expand_input)
		{
			char *expanded = expand_token(shell, input);
			free(input);
			input = expanded;
		}
		ft_putendl_fd(input, fd);
		free(input);
	}
}

char *read_into_heredoc(t_shell *shell, char *eof)
{
	char     *filename = generate_unique_filename(shell);
	const int fd = open(filename, O_WRONLY | O_CREAT);

	if (fd == -1)
	{
		log_message(LOG_ERROR, "cant create here document: %s", strerror(errno));
		return NULL;
	}
	read_input(shell, eof, fd);
	close(fd);
	if (errno == ENOMEM)
		error_fatal(shell, "readline malloc failure", MALLOC_FAIL);
	return filename;
}