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
	printf("%d\n", argument_count);
	argument_count++;
	// argument_count = argument_count == ft_array_size(command->args) ? 0 : argument_count;
	return !command->args[argument_count];
}

bool process_token(t_command *command, const t_token *token)
{
	static t_token_type prv_token_type = NONE;

	if (!is_expected_token(prv_token_type, token->type))
		return log_syntax_error(token, prv_token_type);
	if (token->type == WORD)
	{
		if (is_redirect(prv_token_type))
		{
			if (process_redirect(command, token, prv_token_type))
				return 1;
		}
		if (process_word(command, token))
			return 1;
	}
	prv_token_type = token->type;
	return false;
}
