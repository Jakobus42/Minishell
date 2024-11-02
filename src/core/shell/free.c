/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 14:51:14 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/11/02 15:38:55 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/shell/shell.h"

void	free_token(void *content)
{
	t_token	*token;

	token = (t_token *)content;
	free(token->value);
	free(token);
}

void	free_redirs(t_list *redirs, size_t shell_lvl)
{
	t_redirection	*redir;
	t_list			*del;

	while (redirs)
	{
		redir = (t_redirection *)redirs->content;
		if (redir->type == HEREDOC && shell_lvl == 0 && access(redir->file_name,
				F_OK) == 0)
			unlink(redir->file_name);
		free(redir->file_name);
		free(redir);
		del = redirs;
		redirs = redirs->next;
		free(del);
	}
}

void	free_commands(t_list *commands, size_t shell_lvl)
{
	t_command	*command;
	t_list		*del;
	int			i;

	i = 0;
	while (commands)
	{
		command = (t_command *)commands->content;
		free_redirs(command->redirs, shell_lvl);
		while (i < command->argc)
		{
			free(command->args[i]);
			i++;
		}
		free(command->args);
		free(command);
		del = commands;
		commands = commands->next;
		free(del);
	}
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
	free_commands(shell->pipeline.commands, shell->shell_lvl);
	ft_lstclear(&shell->tokens, &free_token);
	free(shell->exec.pids);
	free(shell->input);
	ft_bzero(&shell->exec, sizeof(shell->exec));
	ft_bzero(&shell->pipeline, sizeof(shell->pipeline));
	ft_bzero(&shell->tokens, sizeof(shell->tokens));
}
