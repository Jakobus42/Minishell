/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 14:45:57 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/11/02 16:31:57 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "core/shell/shell.h"
# include <stdint.h>

typedef struct s_exec
{
	pid_t	*pids;
	int		pipe_fd[2];
	int		prv_pipe;
	int		infile;
	int		outfile;
	bool	exit;
	int		exit_count;

}			t_exec;

/*CHECK EXECUTABLE*/
char		*is_executable(t_shell *shell, char *cmd);

/*REDIRECTIONS*/
void		check_files(t_shell *shell, t_list *redirs);
void		redirect(t_shell *shell, int current_command);

/*EXECUTOR*/
bool		execute_pipeline(t_shell *shell);
bool		execute(t_shell *shell);

/*EXECUTOR UTILS*/
void		close_fds(t_exec *exec);
bool		init_execution(t_shell*shell, t_exec *exec, int num_cmds);
int			wait_for_children(t_shell*shell, pid_t *pids, int num_cmds);

#endif // EXECUTOR_H