#include "core/parser/parser.h"
#include "core/expander/expander.h"
#include "core/shell/shell.h"
#include <fcntl.h>

static char *generate_unique_filename(t_shell *shell) {
	char* filename;
	int fd;
	int i = 0;
	const int N = 20;

	fd = open("/dev/urandom", O_RDONLY);
	if(fd == -1) {
		log_message(LOG_ERROR, "/dev/urandmom: %s", strerror(errno));
		return NULL;
	}
	filename = ft_calloc(sizeof(char), N + 1);
	if(!filename)
		return(close(fd), error_fatal(shell, "read in generate_unique_filename", 1), NULL);
	if(read(fd, filename, N) == -1)
		return(close(fd), error_fatal(shell, "read in generate_unique_filename", 1), NULL);
	close(fd);
	while(filename[i]) {
		if(!ft_isalnum(filename[i]))
			filename[i] = 'x';
		i++;
	}
	return filename;
}

char* remove_quotes(char* eof) {
	char* result = eof;
	char quote = 0;
	int i = 0;
	while(*eof) {
		if(update_quote_state(&quote, *eof))
			eof++;
		else {
			result[i] = *eof;
			eof++;
			i++;
		}
	}
	result[i] = '\0';
	return result;
}

static void read_input(t_shell* shell, char* eof, int fd) {
	const bool should_expand_input = (!ft_strchr(eof, '\'') && !ft_strchr(eof, '\"'));
	const char* eof_no_quotes = remove_quotes(eof);
	char *input;

	while((input = readline("> "))) {
		if(!ft_strcmp(eof_no_quotes, input))
			break ;
		if(should_expand_input) {
			char* expanded = expand_token(shell, input);
			free(input);
			input = expanded;
		}
		ft_putendl_fd(input, fd);
		free(input);
	}
}

char* read_into_heredoc(t_shell* shell, char* eof) {
	char* filename = generate_unique_filename(shell);
	int fd = open(filename, O_WRONLY | O_CREAT);

	if(fd == -1) {
		log_message(LOG_ERROR, "cant create here document: %s", strerror(errno));
		return NULL;
	}
    read_input(shell, eof, fd);
	close(fd);
	if(errno == ENOMEM)
		error_fatal(shell, "readline malloc failure", MALLOC_FAIL);
	return filename;
}