/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 20:27:22 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/10/31 19:47:48 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/builtins/builtins.h"
#include "core/shell/shell.h"
#include "libft/ft_printf_fd.h"
#include "core/shell/signal.h"
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

bool	init_execution(t_exec *exec, int num_cmds)
{
	exec->pids = ft_calloc(num_cmds, sizeof(pid_t));
	if (!exec->pids)
		return (perror("calloc failed"), true);
	exec->infile = -1;
	exec->outfile = -1;
	exec->pipe_fd[0] = -1;
	exec->pipe_fd[1] = -1;
	exec->prv_pipe = -1;
	exec->exit = false;
	exec->exit_count = 0;
	return (false);
}

int	wait_for_children(pid_t *pids, int num_cmds)
{
	bool print = true;
	int i = 0;
	int error_code = 0;

	i = 0;
	error_code = 0;
	while (i < num_cmds && waitpid(pids[i], &error_code, 0) != -1)
	{
		if (WIFEXITED(error_code))
			error_code = WEXITSTATUS(error_code);
		else if (WIFSIGNALED(error_code)) {
			error_code = WTERMSIG(error_code) + 128;
			if(error_code == CTRL_C && print) {
				print = false;
				ft_putendl_fd("", 1);
			} else if(error_code == CTRL_BACKLASH && print) {
				print = false;
				ft_putendl_fd("Quit (core dumped)\n", 2);
			}
		}
		i++;
	}
	return (error_code);
}
