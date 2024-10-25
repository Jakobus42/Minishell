#include "../../../include/core/shell.h"
#include "libft/ft_printf_fd.h"

void close_fds(t_exec *exec)
{
	if (exec->infile != -1 && exec->infile != STDIN_FILENO)
		close(exec->infile);
	if (exec->outfile != -1 && exec->outfile != STDOUT_FILENO)
		close(exec->outfile);
	if (exec->prv_pipe != -1 && exec->prv_pipe != STDIN_FILENO)
		close(exec->prv_pipe);
	if (exec->pipe_fd[0] != -1 && exec->pipe_fd[0] != STDIN_FILENO)
		close(exec->pipe_fd[0]);
	if (exec->pipe_fd[1] != -1 && exec->pipe_fd[1] != STDOUT_FILENO)
		close(exec->pipe_fd[1]);
}

static void execute_command(t_shell *shell, t_command *command, int current_command)
{
	char *cmd;
	char *path;

	shell->exec.infile = check_filein(command->redir);
	shell->exec.outfile = check_fileout(command->redir);
	redirect(shell, current_command);
	close_fds(&shell->exec);
	cmd = command->args[0];
	// if (is_builtin(cmd))
	// 	return (execute_builtin(shell, command));
	path = is_executable(shell, cmd);
	if (!path)
		error_exit(shell, NULL, errno);
	int error = execve(path, command->args, convert_env_to_array(shell->env));
	error_exit(shell, "execve", error);
}

bool init_execution(t_exec *exec, int num_cmds)
{
	exec->pids = ft_calloc(num_cmds, sizeof(pid_t));
	if (!exec->pids)
		return (perror("calloc failed"), true);
	exec->infile = -1;
	exec->outfile = -1;
	exec->pipe_fd[0] = -1;
	exec->pipe_fd[1] = -1;
	exec->prv_pipe = -1;
	return false;
}

bool wait_for_children(pid_t *pids, int num_cmds)
{
	int i = 0;
	int error_code;

	while (i < num_cmds && waitpid(pids[i], &error_code, 0) != -1)
	{
		if (WIFEXITED(error_code))
			error_code = WEXITSTATUS(error_code);
		else if (WIFSIGNALED(error_code))
			error_code = WTERMSIG(error_code) + 128;
		i++;
	}
	return error_code;
}

bool execute_pipeline(t_shell *shell)
{
	t_list    *commands;
	t_command *cmd;
	int        i = 0;

	commands = shell->pipeline.commands;
	while (commands)
	{
		cmd = commands->content;
		if (shell->pipeline.num_commands > 1 && pipe(shell->exec.pipe_fd) == -1)
			return (true);
		shell->exec.pids[i] = fork();
		if (shell->exec.pids[i] == -1)
			return (true);
		else if (shell->exec.pids[i] == 0)
		{
			execute_command(shell, cmd, i);
		}
		if (shell->pipeline.num_commands > 1)
		{
			close(shell->exec.pipe_fd[1]);
			if (shell->exec.prv_pipe != -1 && shell->exec.prv_pipe != STDIN_FILENO)
				close(shell->exec.prv_pipe);
			shell->exec.prv_pipe = shell->exec.pipe_fd[0];
		}
		commands = commands->next;
		i++;
	}
	if (shell->exec.prv_pipe != -1 && shell->exec.prv_pipe != STDIN_FILENO)
		close(shell->exec.prv_pipe);
	shell->error_code = wait_for_children(shell->exec.pids, shell->pipeline.num_commands);
	printf("error_code: %d\n", shell->error_code);
	return false;
}

bool execute(t_shell *shell)
{
	if (init_execution(&shell->exec, shell->pipeline.num_commands))
		return true;
	// if (shell->pipeline.num_commands == 1 && is_builtin(((t_command*)shell->pipeline.commands->content)->args[0])) {
	// 	return execute_single_builtin(shell, ((t_command*)shell->pipeline.commands->content));
	// }
	// else
	return execute_pipeline(shell);
}
