#include "core/shell/shell.h"
#include "fcntl.h"

int check_filein(t_list *redirs)
{
	int            f_in;
	t_redirection *redir;

	f_in = 0;
	while (redirs)
	{
		redir = (t_redirection *) redirs->content;
		if ((redir->type == REDIRECT_IN || redir->type == HEREDOC) && redir->file_name)
		{
			if (f_in && f_in != -1)
				close(f_in);
			f_in = open(redir->file_name, O_CREAT | O_RDONLY, 0644);
			if (f_in == -1 || access(redir->file_name, R_OK))
				return (perror(redir->file_name), -1);
		}
		redirs = redirs->next;
	}
	return (f_in);
}

int check_fileout(t_list *redirs)
{
	int            f_out;
	t_redirection *redir;

	f_out = 0;
	while (redirs)
	{
		redir = (t_redirection *) redirs->content;
		if (redir->type == REDIRECT_OUT && redir->file_name)
		{
			if (f_out && f_out != -1)
				close(f_out);
			f_out = open(redir->file_name, O_CREAT | O_TRUNC | O_WRONLY, 0644);
			if (f_out == -1 || access(redir->file_name, W_OK))
				return (perror(redir->file_name), -1);
		}
		else if (redir->type == REDIRECT_APPEND && redir->file_name)
		{
			if (f_out && f_out != -1)
				close(f_out);
			f_out = open(redir->file_name, O_CREAT | O_APPEND | O_RDWR, 0644);
			if (f_out == -1 || access(redir->file_name, R_OK) || access(redir->file_name, W_OK))
				return (perror(redir->file_name), -1);
		}
		redirs = redirs->next;
	}
	return (f_out);
}

void redirect(t_shell *shell, int current_command)
{
	if (shell->exec.infile == -1 || shell->exec.outfile == -1)
	{
		close_fds(&shell->exec);
		error_fatal(shell, NULL, 1);
	}
	if (shell->exec.infile)
	{
		if (dup2(shell->exec.infile, STDIN_FILENO) == -1)
			return (perror("dup2 infile failed"));
	}
	else if (current_command > 0 && shell->exec.prv_pipe != -1)
	{
		if (dup2(shell->exec.prv_pipe, STDIN_FILENO) == -1)
			return (perror("dup2 prv_pipe failed"));
	}
	if (shell->exec.outfile)
	{
		if (dup2(shell->exec.outfile, STDOUT_FILENO) == -1)
			return (perror("dup2 outfile failed"));
	}
	else if (shell->pipeline.num_commands > 0 &&
	         current_command != shell->pipeline.num_commands - 1)
	{
		if (dup2(shell->exec.pipe_fd[1], STDOUT_FILENO) == -1)
			return (perror("dup2 shell->exec.pipe_fd[1] failed"));
	}
	close_fds(&shell->exec);
}
