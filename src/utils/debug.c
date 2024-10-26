#include "../../include/core/shell.h"
#include "../../include/utils/utils.h"

void debug_print_env(t_list *env)
{
	while (env)
	{
		t_pair *pair = (t_pair *) env->content;
		if (pair)
			printf("Key: %s, Value: %s\n", pair->key, pair->value);
		else
			printf("Env content is NULL\n");
		env = env->next;
	}
}

void debug_print_redirections(t_list *redir)
{
	int i = 0;
	if (!redir)
		return;
	printf("\n");
	while (redir)
	{
		t_redirection *redirection = (t_redirection *) redir->content;
		if (redirection)
			printf("filename: %s, type: %s\n", redirection->file_name,
			       token_type_to_str(redirection->type));
		else
			printf("NULL\n");
		redir = redir->next;
		i++;
	}
	printf("\n");
}

void debug_print_pipeline(t_pipeline *pipeline)
{
	int     i = 0;
	t_list *commands = pipeline->commands;
	printf("\n");
	while (commands)
	{
		t_command *command = (t_command *) commands->content;
		if (!command)
			return;
		printf("----- %s%d%s -----\n", GREEN "COMMAND[", i, "]" RESET);
		printf("command->argc: %d\n", command->argc);
		if (command->args)
			for (int i = 0; i < command->argc; ++i)
				printf("command->args[%d]: %s\n", i, command->args[i]);
		else
			printf("NULL\n");
		debug_print_redirections(command->redir);
		commands = commands->next;
		i++;
	}
	printf("\n");
}