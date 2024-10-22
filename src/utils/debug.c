#include "../../include/core/shell.h"
#include "../../include/utils/utils.h"

void debug_print_env(t_env *env)
{
	while (env->data)
	{
		t_pair *pair = (t_pair *) env->data->content;
		if (pair)
		{
			printf("Key: %s, Value: %s\n", pair->key, pair->value);
		}
		else
		{
			printf("Env content is NULL\n");
		}
		env->data = env->data->next;
	}
}

static const char *token_type_to_str(t_token_type type)
{
	switch (type)
	{
	case WORD:
		return "WORD";
	case PIPE:
		return "PIPE";
	case REDIRECT_OUT:
		return "REDIRECT_OUT";
	case REDIRECT_APPEND:
		return "REDIRECT_APPEND";
	case REDIRECT_IN:
		return "REDIRECT_IN";
	case HEREDOC:
		return "HEREDOC";
	case DQ_WORD:
		return "DQ_WORD";
	case SQ_WORD:
		return "SQ_WORD";
	default:
		return "UNKNOWN";
	}
}

void debug_print_tokens(t_tokens *tokens)
{
	while (tokens->data)
	{
		t_token *pair = (t_token *) tokens->data->content;
		if (pair)
		{
			printf("Token: %s, Type: %s\n", pair->value, token_type_to_str(pair->type));
		}
		else
		{
			printf("Token content is NULL\n");
		}
		tokens->data = tokens->data->next;
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
	debug_print_env(&shell->env);
	printf("---------------TOKENS-------------\n");
	debug_print_tokens(&shell->tokens);
	printf("---------------PIPELINE-----------\n");
	debug_print_pipeline(&shell->pipeline);
}