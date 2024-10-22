#include "../../include/utils/utils.h"

void debug_print_env(t_list *env)
{
	while (env)
	{
		t_env *env_content = (t_env *) env->content;
		printf("Key: %s, Value: %s\n", env_content->key, env_content->value);
		env = env->next;
	}
}

void debug_print_tokens(t_list *tokens)
{
	while (tokens)
	{
		t_token *token = (t_token *) tokens->content;
		printf("Token: %s, Type: %s\n", token->token, token->type ? "WORD" : "OPERATOR");
		tokens = tokens->next;
	}
}

void debug_print_pipeline(t_pipeline *pipeline)
{
	printf("num_commands: %d\n", pipeline->num_commands);
	printf("commands:\n");
	for (int i = 0; i < pipeline->num_commands; ++i)
	{
		printf("commands[%d]:\n", i);
		printf("Command: %s", pipeline->commands[i].cmd);
		printf("Arguments:\n");
		ft_print_array(pipeline->commands[i].args);
	}
}

void debug_print_shell(t_shell *shell)
{
	printf("---------------ENV----------------\n");
	debug_print_env(&shell->env);
	printf("---------------TOKENS-------------\n");
	debug_print_tokens(&shell->tokens);
	printf("---------------PIPELINE-----------\n");
	debug_print_pipeline(&shell->pipeline);
}