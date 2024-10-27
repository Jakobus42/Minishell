#include "core/builtins/builtins.h"
#include "core/shell/shell.h"
#include "libft/ft_printf_fd.h"

static void execute_command(t_shell *shell, t_command *command, int current_command)
{
	char *cmd;
	char *path;

	shell->exec.infile = check_filein(command->redirs);
	shell->exec.outfile = check_fileout(command->redirs);
	redirect(shell, current_command);
	cmd = command->args[0];
	if (is_builtin(cmd))
		return (which_builtin(shell, command));
	path = is_executable(shell, cmd);
	if (!path)
		error_fatal(shell, NULL, shell->error_code);
	shell->error_code = execve(path, command->args, convert_env_to_array(shell->env));
	error_fatal(shell, NULL, shell->error_code);
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
			execute_command(shell, cmd, i);
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
	return false;
}

bool execute(t_shell *shell)
{
	t_command	*cmd;
	char		*s;

	cmd = (t_command *)shell->pipeline.commands->content;
	if (init_execution(&(shell->exec), shell->pipeline.num_commands))
		return (true);
	if (!ft_strcmp(cmd->args[0], "exit"))
	{
		s = check_exit(shell, cmd->args);
		if (shell->exec.exit == true)
			ft_putendl_fd("exit", 2);
		if (s)
			ft_putendl_fd(s, 2);
		free_and_null((void **) &s);
		if (shell->exec.exit == true)
			return (false);
		else
			return (true);
	}
	else if (shell->pipeline.num_commands == 1 && is_builtin(cmd->args[0]))
		return (execute_single_builtin(shell, cmd));
	else
		return (execute_pipeline(shell));
}
