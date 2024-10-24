#include "core/parser/parser.h"
#include "core/shell.h"

// TODO: free on malloc fail
// TODO: refactor

bool process_redirect(t_command *command, const t_token *token, t_token_type redirect_type)
{
	t_redirection *redirect = ft_calloc(sizeof(t_redirection), 1);
	if (!redirect)
		return true;
	redirect->file_name = ft_strdup(token->value);
	if (!redirect->file_name)
		return true;
	redirect->type = redirect_type;
	return ft_lstnew_add_back(&command->redir, redirect);
}

static bool process_word(t_command *command, const t_token *token)
{
	static int argument_count = 0;
	command->args[argument_count] = ft_strdup(token->value);
	if (!command->args[argument_count])
		return NULL;
	if (++argument_count == command->argc)
		argument_count = 0;
	return false;
}

bool process_token(t_command *command, const t_token *token, t_token_type prv_token_type)
{
	if (token->type == WORD)
	{
		if (is_redirect(prv_token_type))
		{
			if (process_redirect(command, token, prv_token_type))
				return 1;
		}
		else if (process_word(command, token))
			return 1;
	}
	return false;
}
