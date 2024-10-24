#include "../../../include/core/shell.h"
#include <fcntl.h>

int check_filein(t_command *exec_cmd)
{
	int            f_in;
	t_redirection *redirs;

	f_in = -1;
	while (exec_cmd->redir)
	{
		redirs = (t_redirection *) exec_cmd->redir->content;
		if ((redirs->type == REDIRECT_IN || redirs->type == HEREDOC) && redirs->file_name)
		{
			if (f_in != -1)
				close(f_in);
			f_in = open(redirs->file_name, O_CREAT | O_RDONLY, 0644);
			if (f_in == -1 || access(redirs->file_name, R_OK))
				return (perror(redirs->file_name), -1);
		}
		exec_cmd->redir = exec_cmd->redir->next;
	}
	return (f_in);
}

int check_fileout(t_command *exec_cmd)
{
	int            f_out;
	t_redirection *redirs;

	f_out = -1;
	while (exec_cmd->redir)
	{
		redirs = (t_redirection *) exec_cmd->redir->content;
		if (redirs->type == REDIRECT_OUT && redirs->file_name)
		{
			if (f_out != -1)
				close(f_out);
			f_out = open(redirs->file_name, O_CREAT | O_TRUNC | O_WRONLY, 0644);
			if (f_out == -1 || access(redirs->file_name, W_OK))
				return (perror(redirs->file_name), -1);
		}
		else if (redirs->type == REDIRECT_APPEND && redirs->file_name)
		{
			if (f_out != -1)
				close(f_out);
			f_out = open(redirs->file_name, O_CREAT | O_APPEND | O_RDWR, 0644);
			if (f_out == -1 || access(redirs->file_name, R_OK) || access(redirs->file_name, W_OK))
				return (perror(redirs->file_name), -1);
		}
		exec_cmd->redir = exec_cmd->redir->next;
	}
	return (f_out);
}

void redirect(int *files, int storage, int *pipe_fd)
{
	if (files[0] != -1)
	{
		if (dup2(files[0], STDIN_FILENO) == -1)
			return (perror("dup2 files[0] failed"));
		close(files[0]);
	}
	else if (storage >= 0)
	{
		if (dup2(storage, STDIN_FILENO) == -1)
			return (perror("dup2 storage failed"));
		close(storage);
	}
	if (files[1] != -1)
	{
		if (dup2(files[1], STDOUT_FILENO) == -1)
			return (perror("dup2 files[1] failed"));
		close(files[1]);
	}
	else if (pipe_fd[1] != -1)
	{
		close(pipe_fd[0]);
		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
			return (perror("dup2 pipe_fd[1] failed"));
		close(pipe_fd[1]);
	}
}
