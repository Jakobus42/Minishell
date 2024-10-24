#include "core/shell.h"

void initialize_shell(t_shell *shell, const char **env)
{
	ft_bzero(shell, sizeof(t_shell));
	shell->env = convert_env_to_list(env);
	if (errno == ENOMEM)
		error_exit(shell, "malloc", ENOMEM);
}

static t_list *generate_tokens(const char *input)
{
	t_token *token;
	t_list  *token_list = NULL;

	while ((token = next_token(&input)))
	{
		if (VERBOSE)
			printf("Token: (%s) Type: (%s)\n", token->value,
			       token_type_to_str(token->type));
		t_list *node = ft_lstnew(token);
		if (!node)
			return (free(token->value), free(token), token_list);
		ft_lstadd_back(&token_list, node);
	}
	return token_list;
}

bool setup_pipeline(t_shell *shell, const char *input)
{
	shell->tokens = generate_tokens(input);
	// shell->tokens = expand_tokens(shell->tokens);

	return parse_tokens(shell->tokens, &shell->pipeline);
}