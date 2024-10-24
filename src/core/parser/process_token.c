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

static bool add_arg_to_command(t_command *command, const char *value)
{
	size_t arg_size = ft_array_size(command->args);
	char **new_args = ft_realloc(command->args, sizeof(char *) * arg_size, sizeof(char *) * (arg_size + 2));
	if (!new_args)
		return true;
	command->args = new_args;
	command->args[arg_size] = ft_strdup(value);
	return !command->args[arg_size];
}

static bool process_word(t_command *command, const t_token *token)
{
	if (!command->cmd)
	{
		command->cmd = ft_strdup(token->value);
		return !command->cmd;
	}
	return add_arg_to_command(command, token->value);
}

bool process_token(t_command *command, const t_token *token, t_parser_state *state)
{
	static t_token_type prv_token_type = NONE;
	if (token->type == WORD)
	{
		if (*state == STATE_REDIRECT)
		{
			if (process_redirect(command, token, prv_token_type))
				return true;
			*state = STATE_WORD;
			return false;
		}
		*state = STATE_WORD;
		return process_word(command, token);
		;
	}
	if (is_redirect(token->type))
	{
		if (*state == STATE_WORD || *state == STATE_END)
		{
			prv_token_type = token->type;
			*state = STATE_REDIRECT;
			return false;
		}
	}
	return false;
}
