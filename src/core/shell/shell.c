#include "../../../include/core/shell.h"

void initialize_shell(t_shell *shell)
{
	ft_bzero(shell, sizeof(t_shell));
	// TODO: init env
}

static void reset_tokens(t_list *tokens)
{
	while (tokens)
	{
		t_token *token = (t_token *) tokens;
		reset_token(token);
		tokens = tokens->next;
	}
}

static void reset_env(t_list *env)
{
	while (env)
	{
		t_env *env_node = (t_env *) env;
		reset_env_node(env_node);
		env = env->next;
	}
}

void reset_shell(t_shell *shell)
{
	reset_pipeline(&shell->pipeline);
	reset_env(shell->env);
	reset_tokens(shell->tokens);
	ft_bzero(shell, sizeof(t_shell));
}