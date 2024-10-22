#include "../../include/utils/utils.h"

void debug_print_env(t_list *env)
{
	while (env)
	{
		t_env *env_content = (t_env *) env->content;
		if (env->content)
		{
			printf("Key: %s, Value: %s\n", env_content->key, env_content->value);
		}
		else
		{
			printf("Env content is NULL\n");
		}
		env = env->next;
	}
}

void debug_print_tokens(t_list *tokens)
{
	while (tokens)
	{
		t_token *token = (t_token *) tokens->content;
		if (token)
		{
			printf("Token: %s, Type: %s\n", token->token, token->type ? "WORD" : "OPERATOR");
		}
		else
		{
			printf("Token is NULL\n");
		}
		tokens = tokens->next;
	}
}

void debug_print_pipeline(t_pipeline *pipeline)
{
	printf("num_commands: %d\n", pipeline->num_commands);
	printf("commands:\n");
	while (pipeline->commands)
	{
		t_command *command = (t_command *) pipeline->commands->content;
		printf("Command: %s", command->cmd);
		printf("Arguments:\n");
		ft_print_array(command->args);
	}
}

void debug_print_shell(t_shell *shell)
{
	printf("---------------ENV----------------\n");
	debug_print_env(shell->env);
	printf("---------------TOKENS-------------\n");
	debug_print_tokens(shell->tokens);
	printf("---------------PIPELINE-----------\n");
	debug_print_pipeline(&shell->pipeline);
}