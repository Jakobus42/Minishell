#include "../../include/core/shell.h"
#include "../../include/utils/utils.h"

void debug_print_env(t_list *env)
{
	printf("------------------------------------------------\n");
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

void debug_print_redirections(t_command *command)
{
	printf("------------------------------------------------\n");
	while (command->redir)
	{
		t_redirection *redirection = (t_redirection *) command->redir->content;
		if (redirection)
			printf("Filename: %s, type: %s\n", redirection->file_name,
			       token_type_to_str(redirection->type));
		else
			printf("NULL\n");
		debug_print_redirections(command);
		command->redir = command->redir->next;
	}
}

void debug_print_pipeline(t_pipeline *pipeline)
{
	printf("------------------------------------------------\n");
	printf("num_commands: %d\n", pipeline->num_commands);
	t_list *commands = pipeline->commands;
	while (commands)
	{
		t_command *command = (t_command *) commands->content;
		if (!command)
			return;
		printf("Command: %s \n", command->cmd);
		printf("Arguments: \n");
		if (command->args)
			for (int i = 0; command->args[i]; ++i)
				printf("command->args[%d]: %s\n", i, command->args[i]);
		else
			printf("NULL\n");
		printf("Redirs: ");
		debug_print_redirections(command);
		commands = commands->next;
	}
}