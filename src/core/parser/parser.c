#include "../../../include/core/parser/parser.h"
#include "../../../include/core/shell.h"

static t_command *append_empty_command(t_shell *shell, t_list **commands)
{
	t_command *command = ft_calloc(sizeof(t_command), 1);
	if (!command)
		error_exit(shell, "ft_calloc", ERROR_GENERAL);
	t_list *node = ft_lstnew(command);
	if (!node)
	{
		free(command);
		error_exit(shell, "ft_lstnew", ERROR_GENERAL);
	}
	ft_lstadd_back(commands, node);
	return command;
}

static void parse_token(t_shell *shell, t_pipeline *pipeline, t_token *token)
{
	t_command *command;
	if (!pipeline->commands) // TODO this looks weird, should only happen if a pipe is found ig
		command = append_empty_command(shell, &pipeline->commands);
	if (process_token(command, token))
		pipeline->commands = pipeline->commands->next;
}

bool parse_tokens(t_shell *shell)
{
	t_list *tokens = shell->tokens.data;

	while (tokens)
	{
		t_token *token = (t_token *) tokens->content;
		parse_token(shell, &shell->pipeline, token);
		tokens = tokens->next;
	}
	return true;
}
