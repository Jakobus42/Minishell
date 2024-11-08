/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 14:50:40 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/11/02 16:13:34 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/shell/shell.h"
#include "fcntl.h"

static int	get_infile(int infile, t_redirection *redir)
{
	if (infile && infile != -1)
		close(infile);
	infile = open(redir->file_name, O_RDONLY, 0644);
	if (infile == -1 || access(redir->file_name, R_OK))
		perror(redir->file_name);
	return (infile);
}

static int	get_outfile(int outfile, t_redirection *redir)
{
	if (outfile && outfile != -1)
		close(outfile);
	outfile = open(redir->file_name, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (outfile == -1 || access(redir->file_name, W_OK))
		perror(redir->file_name);
	return (outfile);
}

static int	get_append_file(int outfile, t_redirection *redir)
{
	if (outfile && outfile != -1)
		close(outfile);
	outfile = open(redir->file_name, O_CREAT | O_APPEND | O_RDWR, 0644);
	if (outfile == -1 || access(redir->file_name, R_OK)
		|| access(redir->file_name, W_OK))
		perror(redir->file_name);
	return (outfile);
}

void	check_files(t_shell *shell, t_list *redirs)
{
	t_redirection	*redir;

	shell->exec.infile = 0;
	shell->exec.outfile = 0;
	while (redirs)
	{
		redir = (t_redirection *)redirs->content;
		if (redir->type == NONE)
		{
			shell->exec.infile = -1;
			log_message(LOG_ERROR, "ambiguous redirect\n");
			break ;
		}
		if ((redir->type == REDIRECT_IN || redir->type == HEREDOC)
			&& redir->file_name)
			shell->exec.infile = get_infile(shell->exec.infile, redir);
		else if (redir->type == REDIRECT_OUT && redir->file_name)
			shell->exec.outfile = get_outfile(shell->exec.outfile, redir);
		else if (redir->type == REDIRECT_APPEND && redir->file_name)
			shell->exec.outfile = get_append_file(shell->exec.outfile, redir);
		if (shell->exec.infile == -1 || shell->exec.outfile == -1)
			break ;
		redirs = redirs->next;
	}
}

void	redirect(t_shell *shell, int current_command)
{
	if (shell->exec.infile == -1 || shell->exec.outfile == -1)
		return (close_fds(&shell->exec), error_fatal(shell, NULL, 1));
	if (shell->exec.infile)
	{
		if (dup2(shell->exec.infile, STDIN_FILENO) == -1)
			return (close_fds(&shell->exec), error_fatal(shell, "dup2", 1));
	}
	else if (current_command > 0 && shell->exec.prv_pipe != -1)
	{
		if (dup2(shell->exec.prv_pipe, STDIN_FILENO) == -1)
			return (close_fds(&shell->exec), error_fatal(shell, "dup2", 1));
	}
	if (shell->exec.outfile)
	{
		if (dup2(shell->exec.outfile, STDOUT_FILENO) == -1)
			return (close_fds(&shell->exec), error_fatal(shell, "dup2", 1));
	}
	else if (shell->pipeline.num_commands > 0
		&& current_command != shell->pipeline.num_commands - 1)
	{
		if (dup2(shell->exec.pipe_fd[1], STDOUT_FILENO) == -1)
			return (close_fds(&shell->exec), error_fatal(shell, "dup2", 1));
	}
	close_fds(&shell->exec);
}
