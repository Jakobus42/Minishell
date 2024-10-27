#include "core/parser/parser.h"
#include "core/shell/shell.h"

static size_t count_args(const t_list *tokens)
{
	size_t       count = 0;
	t_token     *token;
	t_token_type prv_token_type = NONE;

	while (tokens)
	{
		token = (t_token *) tokens->content;
		if (token->type == PIPE)
			break;
		if (!is_redirect(prv_token_type) && token->type == WORD)
			count++;
		prv_token_type = token->type;
		tokens = tokens->next;
	}
	return count;
}

static t_command *construct_command(t_shell *shell, size_t argc)
{
	t_command *command;
	command = ft_calloc(sizeof(t_command), 1);
	if (!command)
		error_fatal(shell, "ft_calloc in construct_command", MALLOC_FAIL);
	command->argc = argc;
	command->args = ft_calloc(sizeof(char *), (argc + 1));
	if (!command->args)
	{
		free(command);
		error_fatal(shell, "ft_calloc in construct_command", MALLOC_FAIL);
	}
	return command;
}

static void append_command_to_pipeline(t_shell *shell, t_command *command)
{
	if (ft_lstnew_add_back(&shell->pipeline.commands, command))
		error_fatal(shell, "ft_lstnew_add_back in append_command_to_pipeline", MALLOC_FAIL);
}

bool parse_tokens(t_shell *shell, const t_list *tokens)
{
	t_token     *token;
	t_command   *command = NULL;
	t_token_type prv_token_type = NONE;

	if (validate_token_sequence(tokens))
		return true;

	while (tokens)
	{
		token = tokens->content;
		if (token->type == PIPE)
		{
			tokens = tokens->next;
			token = tokens->content;
			command = NULL;
		}
		if (!command)
		{
			command = construct_command(shell, count_args(tokens));
			append_command_to_pipeline(shell, command);
		}
		process_token(shell, command, token, prv_token_type);
		prv_token_type = token->type;
		if (tokens)
			tokens = tokens->next;
	}
	return false;
}
