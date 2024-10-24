#include "../../../include/core/shell.h"
#include <fcntl.h>

int check_filein(t_list *redirs)
{
	int            f_in;
	t_redirection *redir;

	f_in = -1;
	while (redirs)
	{
		redir = (t_redirection *) redirs->content;
		if ((redir->type == REDIRECT_IN || redir->type == HEREDOC) && redir->file_name)
		{
			if (f_in != -1)
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

	f_out = -1;
	while (redirs)
	{
		redir = (t_redirection *) redirs->content;
		if (redir->type == REDIRECT_OUT && redir->file_name)
		{
			if (f_out != -1)
				close(f_out);
			f_out = open(redir->file_name, O_CREAT | O_TRUNC | O_WRONLY, 0644);
			if (f_out == -1 || access(redir->file_name, W_OK))
				return (perror(redir->file_name), -1);
		}
		else if (redir->type == REDIRECT_APPEND && redir->file_name)
		{
			if (f_out != -1)
				close(f_out);
			f_out = open(redir->file_name, O_CREAT | O_APPEND | O_RDWR, 0644);
			if (f_out == -1 || access(redir->file_name, R_OK) || access(redir->file_name, W_OK))
				return (perror(redir->file_name), -1);
		}
		redirs = redirs->next;
	}
	return (f_out);
}

void redirect(int *files, int *pipe_fd, int i, int x)
{
	if (files[0] != -1)
	{
		puts("files[0]");
		if (dup2(files[0], STDIN_FILENO) == -1)
			return (perror("dup2 files[0] failed"));
	}
	else if (files[2] != -1)
	{
		puts("files[2]");
		if (dup2(files[2], STDIN_FILENO) == -1)
			return (perror("dup2 storage failed"));
	}
	else if (i > 0 && pipe_fd[0] != -1)
	{
		puts("pipe_fd[0]");
		if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
			return (perror("dup2 pipe_fd[0] failed"));
	}
	if (files[1] != -1)
	{
		puts("files[1]");
		if (dup2(files[1], STDOUT_FILENO) == -1)
			return (perror("dup2 files[1] failed"));
	}
	else if (i < x - 1 && pipe_fd[1] != -1)
	{
		puts("pipe_fd[1]");
		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
			return (perror("dup2 pipe_fd[1] failed"));
	}
}
