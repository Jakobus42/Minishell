#include "core/expander/expander.h"
#include "core/parser/parser.h"
#include "core/shell/shell.h"
#include <fcntl.h>

static void	process_redirect(t_shell *shell, t_command *cmd,
		const t_token *token, const t_token_type redir_type)
{
	t_redirection	*redirect;

	if (!token->value)
		return ;
	redirect = ft_calloc(sizeof(t_redirection), 1);
	if (!redirect)
		error_fatal(shell, "ft_calloc in process_redirect", MALLOC_FAIL);
	redirect->type = redir_type;
	redirect->file_name = ft_strdup(token->value);
	if (!redirect->file_name)
	{
		free(redirect);
		error_fatal(shell, "ft_strdup in process_redirect", MALLOC_FAIL);
	}
	if (ft_lstnew_add_back(&cmd->redirs, redirect))
	{
		free_redir(redirect);
		error_fatal(shell, "ft_lstnew_add_back in process_redirect",
			MALLOC_FAIL);
	}
}

static void	process_word(t_shell *shell, t_command *cmd, const t_token *token)
{
	static int	argument_count = 0;

	cmd->args[argument_count] = ft_strdup(token->value);
	if (!cmd->args[argument_count])
		error_fatal(shell, "ft_strdup in process_word", MALLOC_FAIL);
	if (++argument_count >= cmd->argc)
		argument_count = 0;
}

void	process_token(t_shell *s, t_command *cmd, const t_token *tok,
		t_token_type prv_tok_type)
{
	if (is_redirect(prv_tok_type) && tok->type == WORD)
		process_redirect(s, cmd, tok, prv_tok_type);
	else if (tok->type == WORD)
		process_word(s, cmd, tok);
}
