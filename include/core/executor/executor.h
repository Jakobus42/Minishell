#ifndef EXECUTOR_H
#define EXECUTOR_H

#include "core/shell/shell.h"
#include <stdint.h>

typedef struct s_exec
{
	pid_t *pids;
	int    pipe_fd[2];
	int    prv_pipe;
	int    infile;
	int    outfile;
} t_exec;

/*CHECK EXECUTABLE*/
bool  check_permissions(t_shell *shell, char *cmd);
bool  pre_executable_check(t_shell *shell, char **paths, char *cmd);
char *is_executable(t_shell *shell, char *cmd); //, char **env);

/*REDIRECTIONS*/
int  check_filein(t_list *redirs);
int  check_fileout(t_list *redirs);
void redirect(t_shell *shell, int current_command);

/*EXECUTOR*/
bool execute(t_shell *shell);
void close_fds(t_exec *exec);

#endif // EXECUTOR_H