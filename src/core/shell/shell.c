#include "core/shell.h"

void initialize_shell(t_shell *shell, const char **env)
{
	ft_bzero(shell, sizeof(t_shell));
	shell->env.data = convert_env_to_list(env);
	if (errno == ENOMEM)
		error_exit(shell, "malloc", ENOMEM);
	// debug_print_env(&shell->env);
}

void append_command_to_pipeline(t_shell *shell, t_command *command)
{
	t_list *node = ft_lstnew(command);
	if (!node)
		error_exit(shell, "malloc", ENOMEM);
	ft_lstadd_back(&shell->pipeline.commands, node);
}

bool setup_pipeline(t_shell *shell, const char *input)
{
	t_command *command;
	t_token   *token;

	while ((token = next_token(&input)))
	{
		if (VERBOSE)
			printf("Token: (%s) Type: (%s)\n", token->value,
			       token_type_to_str(token->type));
		command = parse_token(token); // could return no command if the token is a operator
		if (errno == ENOMEM)
			error_exit(shell, "malloc", ENOMEM);
		if (command)
			append_command_to_pipeline(shell, command);
		free(token->value); // tmp
		free(token);
	}
	return SUCCESS;
}