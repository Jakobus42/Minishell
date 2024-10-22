#include "../../../include/core/shell.h"
#include <fcntl.h>
#include <unistd.h>

void check_files(t_command *exec_cmd)
{
	exec_cmd->exec.filein = -1;
	exec_cmd->exec.fileout = -1;
	while (exec_cmd)
	{
		if ((exec_cmd->redir->type == REDIR_INPUT || exec_cmd->redir->type == REDIR_HEREDOC) &&
		    exec_cmd->redir->file_name)
		{
			if (exec_cmd->exec.filein != -1)
				close(exec_cmd->exec.filein);
			exec_cmd->exec.filein = open(exec_cmd->redir->file_name, O_CREAT | O_RDONLY, 0644);
			if (exec_cmd->exec.filein == -1 || access(exec_cmd->exec.filein, R_OK))
				return (perror(exec_cmd->redir->file_name));
		}
		else if (exec_cmd->redir->type == REDIR_OUTPUT && exec_cmd->redir->file_name)
		{
			if (exec_cmd->exec.fileout != -1)
				close(exec_cmd->exec.fileout);
			exec_cmd->exec.fileout = open(exec_cmd->redir->file_name, O_CREAT | O_TRUNC | O_WRONLY, 0644);
			if (exec_cmd->exec.fileout == -1 || access(exec_cmd->exec.fileout, R_OK))
				return (perror(exec_cmd->redir->file_name));
		}
		else if (exec_cmd->redir->type == REDIR_APPEND && exec_cmd->redir->file_name)
		{
			if (exec_cmd->exec.fileout != -1)
				close(exec_cmd->exec.fileout);
			exec_cmd->exec.fileout = open(exec_cmd->redir->file_name, O_CREAT | O_APPEND | O_RDWR, 0644);
			if (exec_cmd->exec.fileout == -1 || access(exec_cmd->exec.fileout, R_OK) ||
			    access(exec_cmd->exec.fileout, W_OK))
				return (perror(exec_cmd->redir->file_name));
		}
		exec_cmd = exec_cmd->next;
	}
}

uint8_t execute_command(t_shell *shell, t_command *command)
{
}

void execute_pipeline(t_shell *shell)
{
	t_exec exec;
	int    prv_pipe;

	/*
	    if(commands == 1 && is_builtin) {
	        builtin
	    } //else execute builtins in child
	    while(commands) {
	        pipe(exec.fd);
	        fork() {
	            redirect_comamnd();
	            execute_command();
	        }
	        close(exec.fd[1])
	        if(not first command)
	            prv_pipe = exec.fd[0];
	        commands = commands->next;
	    }
	*/
}

void redirect(t_shell *shell, int i)
{
	t_command exec_cmd;
	// check_filein(shell);
	// check_fileout(shell);

	exec_cmd = shell->pipeline.commands[i];

	if (pipe(pipe_fd) == -1)
		return (perror("pipe failed"));
	/*REDIRECT INPUT, CHECK IF SMTH STORED*/
	if ((shell->pipeline.commands->redir->type == REDIR_INPUT ||
	     shell->pipeline.commands->redir->type == REDIR_HEREDOC) &&
	    shell->pipeline.commands->redir->file_name)
	{
		if (dup2(shell->pipeline.commands->redir->file_name, STDIN_FILENO) == -1)
			return (perror("dup2 filein failed"));
	}
	else if (store_fd == -1 && shell->pipeline.commands->redir->type == REDIR_INPUT)
	{
		if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
			return (perror("dup2 pipe_fd[0] failed"));
	}
	else if (store_fd >= 0 && shell->pipeline.commands->redir->type == REDIR_INPUT)
	{
		if (dup2(store_fd, STDIN_FILENO) == -1)
			return (perror("dup2 store_fd failed"));
	}
	/*REDIRECT OUTPUT, CHECK IF NEEDS TO BE STORED IN STORAGE?*/
	if ((shell->pipeline.commands->redir->type == REDIR_OUTPUT ||
	     shell->pipeline.commands->redir->type == REDIR_APPEND) &&
	    shell->pipeline.commands->redir->file_name)
	{
		if (dup2(shell->pipeline.commands->redir->file_name, STDOUT_FILENO) == -1)
			return (perror("dup2 fileout failed"));
	}
	else if (shell->pipeline.num_commands > 1 &&
	         (shell->pipeline.commands->redir->type == REDIR_OUTPUT ||
	          shell->pipeline.commands->redir->type == REDIR_APPEND))
	{
		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
			return (perror("dup2 pipe_fd[1] failed"));
	}
}
