#include "core/shell/shell.h"

void	free_token(void *content)
{
	t_token	*token;

	token = (t_token *)content;
	free(token->value);
	free(token);
}

void	free_redir(void *content)
{
	t_redirection	*redir;

	redir = (t_redirection *)content;
	if (redir->type == HEREDOC && access(redir->file_name, F_OK) == 0)
		unlink(redir->file_name);
	free(redir->file_name);
	free(content);
}

void	free_command(void *content)
{
	t_command	*command;
	int			i;

	i = 0;
	command = (t_command *)content;
	ft_lstclear(&command->redirs, &free_redir);
	while (i < command->argc)
	{
		free(command->args[i]);
		i++;
	}
	free(command->args);
	free(command);
}

void	free_env(void *content)
{
	t_pair	*pair;

	pair = (t_pair *)content;
	free(pair->value);
	free(pair->key);
	free(pair);
}

void	reset_shell(t_shell *shell)
{
	errno = 0;
	ft_lstclear(&shell->pipeline.commands, &free_command);
	ft_lstclear(&shell->tokens, &free_token);
	free(shell->exec.pids);
	free(shell->input);
	ft_bzero(&shell->exec, sizeof(shell->exec));
	ft_bzero(&shell->pipeline, sizeof(shell->pipeline));
	ft_bzero(&shell->tokens, sizeof(shell->tokens));
}
