#include "core/expander/expander.h"
#include "core/parser/parser.h"
#include "core/shell/shell.h"
#include <fcntl.h>

static void process_redirect(t_shell *shell, t_command *command, const t_token *token, const t_token_type redirect_type)
{
	if (!token->value)
		return;
	t_redirection *redirect = ft_calloc(sizeof(t_redirection), 1);
	if (!redirect)
		error_fatal(shell, "ft_calloc in process_redirect", MALLOC_FAIL);
	redirect->type = redirect_type;
	redirect->file_name = ft_strdup(token->value);
	if (!redirect->file_name)
	{
		free(redirect);
		error_fatal(shell, "ft_strdup in process_redirect", MALLOC_FAIL);
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
