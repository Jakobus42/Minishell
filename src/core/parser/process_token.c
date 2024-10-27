#include "core/parser/parser.h"
#include "core/shell/shell.h"
#include "core/expander/expander.h"
#include <fcntl.h>

char *generate_unique_filename(t_shell *shell) {
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

char* read_into_heredoc(t_shell* shell, char* eof) {
	const bool should_expand_input = (!ft_strchr(eof, '\'') && !ft_strchr(eof, '\"'));
	char* filename = generate_unique_filename(shell);
	char *input;
	int fd = open(filename, O_WRONLY | O_CREAT);

	if(fd == -1) {
		log_message(LOG_ERROR, "cant create here document: %s", strerror(errno));
		return NULL;
	}
	if(!should_expand_input) {
		eof = expand_token(shell, eof);
	}
	while((input = readline("> "))) {
		if(!ft_strcmp(input, eof))
			break ;
		if(should_expand_input) {
			char* expanded = expand_token(shell, input);
			free(input);
			input = expanded;
		}
		ft_putendl_fd(input, fd);
		free(input);
	}
	if(!should_expand_input)
		free((char*)eof);
	close(fd);
	if(errno == ENOMEM)
		error_fatal(shell, "readline malloc failure", MALLOC_FAIL);
	return filename;
}

static void process_redirect(t_shell *shell, t_command *command, const t_token *token, t_token_type redirect_type)
{
	t_redirection *redirect = ft_calloc(sizeof(t_redirection), 1);
	if (!redirect)
		error_fatal(shell, "ft_calloc in process_redirect", MALLOC_FAIL);
	redirect->type = redirect_type;
	if(redirect->type == HEREDOC) {
		redirect->file_name = read_into_heredoc(shell, token->value);
	} else {
		redirect->file_name = ft_strdup(token->value);
		if (!redirect->file_name)
		{
			free(redirect);
			error_fatal(shell, "ft_strdup in process_redirect", MALLOC_FAIL);
		}
	}
	if (ft_lstnew_add_back(&command->redirs, redirect))
	{
		free_redir(redirect);
		error_fatal(shell, "ft_lstnew_add_back in process_redirect", MALLOC_FAIL);
	}
}

static void process_word(t_shell *shell, t_command *command, const t_token *token)
{
	static int argument_count = 0;
	command->args[argument_count] = ft_strdup(token->value);
	if (!command->args[argument_count])
		error_fatal(shell, "ft_strdup in process_word", MALLOC_FAIL);
	if (++argument_count >= command->argc)
		argument_count = 0;
}

void process_token(t_shell *shell, t_command *command, const t_token *token, t_token_type prv_token_type)
{
	if (is_redirect(prv_token_type) && token->type == WORD)
		process_redirect(shell, command, token, prv_token_type);
	else if (token->type == WORD)
		process_word(shell, command, token);
}
