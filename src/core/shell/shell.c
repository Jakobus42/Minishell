#include "core/shell.h"

void initialize_shell(t_shell *shell)
{
	ft_bzero(shell, sizeof(t_shell));
}

bool setup_pipeline(t_shell *shell, const char *input)
{
	t_command *command;
	t_token   *token;
	t_list    *node;

	while ((token = next_token(&input)))
	{
		if (VERBOSE)
			printf("Token: (%s) Type: (%s)\n", token->value,
			       token_type_to_str(token->type));
		command = parse_token(token);
		node = ft_lstnew(command);
		if (!node)
			error_exit(shell, "malloc", ENOMEM);
		ft_lstadd_back(&shell->pipeline.commands, node);
		free(token);
	}
	if (errno == ENOMEM)
		error_exit(shell, "malloc", ENOMEM);
	return SUCCESS;
}