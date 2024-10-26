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
		return (free(redirect), true);
	redirect->type = redirect_type;
	if (ft_lstnew_add_back(&command->redirs, redirect))
		return (free(redirect->file_name), free(redirect), true);
	return false;
}

static bool process_word(t_command *command, const t_token *token)
{
	static int argument_count = 0;
	command->args[argument_count] = ft_strdup(token->value);
	if (!command->args[argument_count])
		return true;
	if (++argument_count >= command->argc)
		argument_count = 0;
	return false;
}

bool process_token(t_command *command, const t_token *token, t_token_type prv_token_type)
{
	if (token->type != WORD)
		return false;
	if (is_redirect(prv_token_type))
		return process_redirect(command, token, prv_token_type);
	return process_word(command, token);
}
