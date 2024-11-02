/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 14:50:35 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/11/02 17:00:49 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/builtins/builtins.h"
#include "core/shell/shell.h"
#include "core/shell/signal.h"
#include "libft/ft_printf_fd.h"
#include <sys/dir.h>

void	close_fds(t_exec *exec)
{
	if (exec->infile != -1 && exec->infile)
		close(exec->infile);
	if (exec->outfile != -1 && exec->outfile)
		close(exec->outfile);
	if (exec->prv_pipe != -1 && exec->prv_pipe != STDIN_FILENO)
		close(exec->prv_pipe);
	if (exec->pipe_fd[0] != -1 && exec->pipe_fd[0] != STDIN_FILENO)
		close(exec->pipe_fd[0]);
	if (exec->pipe_fd[1] != -1 && exec->pipe_fd[1] != STDOUT_FILENO)
		close(exec->pipe_fd[1]);
}

bool	init_execution(t_shell *shell, t_exec *exec, int num_cmds)
{
	exec->pids = ft_calloc(num_cmds, sizeof(pid_t));
	if (!exec->pids)
		error_fatal(shell, "malloc", MALLOC_FAIL);
	exec->infile = -1;
	exec->outfile = -1;
	exec->pipe_fd[0] = -1;
	exec->pipe_fd[1] = -1;
	exec->prv_pipe = -1;
	exec->exit = false;
	exec->exit_count = 0;
	return (false);
}

static bool	error_and_print(int error_code, bool print)
{
	if (error_code == CTRL_C && print)
	{
		print = false;
		ft_putendl_fd("", 1);
	}
	else if (error_code == CTRL_BACKLASH && print)
	{
		print = false;
		ft_putendl_fd("Quit (core dumped)", 2);
	}
	return (print);
}

int	wait_for_children(t_shell *shell, pid_t *pids, int num_cmds)
{
	bool	print;
	int		i;
	int		error_code;

	print = true;
	i = -1;
	error_code = 0;
	(void)pids;
	while (++i < num_cmds)
	{
		if (waitpid(pids[i], &error_code, 0) == -1)
			error_fatal(shell, "waitpid", 1);
		if (WIFEXITED(error_code))
			error_code = WEXITSTATUS(error_code);
		else if (WIFSIGNALED(error_code))
		{
			error_code = WTERMSIG(error_code) + 128;
			print = error_and_print(error_code, print);
		}
	}
	return (error_code);
}
