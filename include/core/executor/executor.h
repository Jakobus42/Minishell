#ifndef EXECUTOR_H
#define EXECUTOR_H

#include "core/shell.h"
#include <stdint.h>

/*CHECK EXECUTABLE*/
bool  check_permissions(t_shell *shell, char *cmd);
bool  pre_executable_check(t_shell *shell, char **paths, char *cmd);
char *is_executable(t_shell *shell, char *cmd); //, char **env);

/*REDIRECTIONS*/
int  check_filein(t_list *redirs);
int  check_fileout(t_list *redirs);
void redirect(int *files, int *pipe_fd, int i, int x);

/*EXECUTOR*/
uint8_t execute_command(t_shell *shell, t_command *command, char **env);
void    execute_pipeline(t_shell *shell, pid_t *pid, int x); //, char **env);
bool    ft_strcmp_bool(const char *s1, const char *s2);

/*BUILTINS*/
bool is_builtin(char *s);
// uint8_t	execute_builtin(t_shell *shell, t_command *cmd);

#endif // EXECUTOR_H