#ifndef BUILTINS_H
#define BUILTINS_H

#include "core/shell/shell.h"

/*BUILTINS*/
bool    is_builtin(char *s);
void    reset_fds(int copy_stdin, int copy_stdout);
void    redirect_builtin(t_shell *shell);
void    set_export(t_shell *shell, t_command *cmd);
void    execute_builtin(t_shell *shell, t_command *cmd);
uint8_t execute_single_builtin(t_shell *shell, t_command *cmd);

/*CD*/
u_int8_t cd_builtin(t_shell *shell);
// u_int8_t	echo_builtin(t_shell *shell);

/*EXPORT*/
bool check_valid_export(const char *key, const char *value);
void print_env(t_list *env);
void print_export(t_list *env);

#endif