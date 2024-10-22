#include "../../../include/core/parser/parser.h"

void reset_redirs(t_list *redirs)
{
	while (redirs)
	{
		t_redirection *redir = (t_redirection *) redirs->content;
		free_and_null((void **) &redir->file_name);
	}
}

static void reset_commands(t_command *command)
{
	reset_redirs(command->redir);
	free_and_null((void **) &command->cmd);
	free_array((void ***) &command->args);
}

void reset_pipeline(t_pipeline *pipeline)
{
	while (pipeline->commands)
	{
		t_command *command = (t_command *) pipeline->commands;
		reset_commands(command);
		pipeline->commands = pipeline->commands->next;
	}
}