/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 20:27:27 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/10/31 19:52:37 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/builtins/builtins.h"
#include "core/shell/shell.h"
#include "core/shell/signal.h"
#include "libft/ft_printf_fd.h"

static void	execute_command(t_shell *shell, t_command *command, int cur_cmd)
{
	char *cmd;
	char *path;
	char	**env;

	shell->shell_lvl++;
	handle_signal(shell, MODE_CHILD);
	check_files(shell, command->redirs);
	redirect(shell, cur_cmd);
	cmd = command->args[0];
	if (!cmd)
		error_fatal(shell, NULL, shell->error_code);
	if (is_builtin(cmd))
	{
		which_builtin(shell, command);
		error_fatal(shell, NULL, 0);
	}
	path = is_executable(shell, cmd);
	if (!path)
		error_fatal(shell, NULL, shell->error_code);
	env = convert_env_to_array(shell, shell->env);
	shell->error_code = execve(path, command->args, env);
	free_array((void ***) &env);
	error_fatal(shell, NULL, shell->error_code);
}

bool	execute_pipeline(t_shell *shell)
{
	t_list		*commands;
	t_command	*cmd;
	int			i;

	i = 0;
	commands = shell->pipeline.commands;
	while (commands)
	{
		cmd = commands->content;
		if (shell->pipeline.num_commands > 1
			&& pipe(shell->exec.pipe_fd) == -1)
			return (true);
		shell->exec.pids[i] = fork();
		if (shell->exec.pids[i] == -1)
			error_fatal(shell, "fork in execute_pipeline failed\n", 1);//FORK?
		else if (shell->exec.pids[i] == 0)
			execute_command(shell, cmd, i);
		if (shell->pipeline.num_commands > 1)
		{
			close(shell->exec.pipe_fd[1]);
			if (shell->exec.prv_pipe != -1
				&& shell->exec.prv_pipe != STDIN_FILENO)
				close(shell->exec.prv_pipe);
			shell->exec.prv_pipe = shell->exec.pipe_fd[0];
		}
		commands = commands->next;
		i++;
	}
	if (shell->exec.prv_pipe != -1 && shell->exec.prv_pipe != STDIN_FILENO)
		close(shell->exec.prv_pipe);
	return (false);
}

bool	execute(t_shell *shell)
{
	t_command	*cmd;
	char		*s;

	cmd = (t_command *) shell->pipeline.commands->content;
	if (init_execution(&(shell->exec), shell->pipeline.num_commands))
		return (true);
	if (!ft_strcmp(cmd->args[0], "exit"))
	{
		s = check_exit(shell, cmd->args);
		if (shell->exec.exit == true && (!s
				|| (s && !ft_strnstr(s, "numeric", ft_strlen(s)))))
			ft_putendl_fd("exit", 2);
		if (s)
			ft_putendl_fd(s, 2);
		if (shell->exec.exit == true)
			return (free_and_null((void **) &s), false);
		else
			return (free_and_null((void **) &s), true);
	}
	else if (shell->pipeline.num_commands == 1 && is_builtin(cmd->args[0]))
		execute_single_builtin(shell, cmd);
	else
	{
		execute_pipeline(shell);
		shell->error_code = wait_for_children(shell->exec.pids,
				shell->pipeline.num_commands);
	}
	return (false);
}
