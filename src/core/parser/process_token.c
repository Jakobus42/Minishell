#include "core/parser/parser.h"
#include "core/shell.h"

static bool is_expected_token(t_parser_state state, t_token_type token_type)
{
	switch (state)
	{
	case STATE_START:
		return token_type == WORD || is_redirect(token_type);
	case STATE_WORD:
		return token_type == WORD || is_redirect(token_type) || token_type == PIPE;
	case STATE_PIPE:
		return token_type == WORD || is_redirect(token_type);
	case STATE_REDIRECT:
		return token_type == WORD;
	default:
		return token_type == WORD;
	}
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
	if (!is_expected_token(*state, token->type))
	{
		dprintf(2, "Unexpected token: %s got: %s expected token of %d\n", token->value,
		        token_type_to_str(token->type), (int) *state);
		return true;
	}
	if (token->type == WORD && process_word(command, token))
	{
		return true;
	}
	*state = STATE_WORD;
	return false;
}