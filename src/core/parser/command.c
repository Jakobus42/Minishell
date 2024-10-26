#include "core/parser/parser.h"
#include "core/shell/shell.h"

size_t count_args(const t_list *tokens)
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

t_command *construct_command(t_shell *shell, size_t argc)
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

void append_command_to_pipeline(t_shell *shell, t_command *command)
{
	if (ft_lstnew_add_back(&shell->pipeline.commands, command))
		error_fatal(shell, "ft_lstnew_add_back in append_command_to_pipeline", MALLOC_FAIL);
}
