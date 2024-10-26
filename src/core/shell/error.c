#include "core/shell.h"
#include "libft/ft_printf_fd.h"

static void free_redirs(t_list *redirs)
{
	while (redirs)
	{
		t_redirection *redir = (t_redirection *) redirs->content;
		if (redir)
		{
			free_and_null((void **) &redir->file_name);
			free_and_null((void **) &redir);
		}
		t_list *del = redirs;
		redirs = redirs->next;
		free_and_null((void **) &del);
	}
}

static void free_command(t_command *command)
{
	free_redirs(command->redirs);
	for (int i = 0; i < command->argc; ++i)
		free_and_null((void **) &command->args[i]);
	free_and_null((void **) &command->args);
	free_and_null((void **) &command);
}

static void free_pipeline(t_pipeline *pipeline)
{
	while (pipeline->commands)
	{
		t_command *command = (t_command *) pipeline->commands->content;
		if (command)
			free_command(command);
		t_list *del = pipeline->commands;
		pipeline->commands = pipeline->commands->next;
		free_and_null((void **) &del);
	}
}

static void free_tokens(t_list *tokens)
{
	while (tokens)
	{
		t_token *content = (t_token *) tokens->content;
		free_and_null((void **) &content->value);
		free_and_null((void **) &content);
		t_list *del = tokens;
		tokens = tokens->next;
		free_and_null((void **) &del);
	}
}

static void free_env(t_list *env)
{
	while (env)
	{
		t_pair *content = (t_pair *) env->content;
		free_and_null((void **) &content->value);
		free_and_null((void **) &content->key);
		free_and_null((void **) &content);
		t_list *del = env;
		env = env->next;
		free(del);
	}
}

void reset_shell(t_shell *shell)
{
	errno = 0;
	free_pipeline(&shell->pipeline);
	free_tokens(shell->tokens);
	free_and_null((void **) &shell->exec.pids);
	ft_bzero(&shell->exec, sizeof(shell->exec));
	ft_bzero(&shell->pipeline, sizeof(shell->pipeline));
	ft_bzero(&shell->tokens, sizeof(shell->tokens));
	shell->error_code = 0;
}

void error_exit(t_shell *shell, const char *error_msg, uint8_t error_code)
{
	if (error_msg)
		perror(error_msg);
	free_env(shell->env);
	reset_shell(shell);
	exit(error_code);
}