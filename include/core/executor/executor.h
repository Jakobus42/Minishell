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
bool		init_execution(t_exec *exec, int num_cmds);
int			wait_for_children(pid_t *pids, int num_cmds);

#endif // EXECUTOR_H