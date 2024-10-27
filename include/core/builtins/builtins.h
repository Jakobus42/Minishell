#ifndef BUILTINS_H
#define BUILTINS_H

#include "core/shell/shell.h"

/*BUILTINS*/
bool    is_builtin(char *s);
void    reset_fds(int copy_stdin, int copy_stdout);
void    redirect_builtin(t_shell *shell);
void    which_builtin(t_shell *shell, t_command *cmd);
uint8_t execute_single_builtin(t_shell *shell, t_command *cmd);

/*CD*/
uint8_t	cd_builtin(t_shell *shell);

/*ECHO*/
bool	check_n(char *token);
int		echo(char **token);

/*EXPORT*/
bool 	check_valid_export(char *s);
char	*checking_vars(char *s);
void 	print_export(t_list *env);
void    set_export(t_shell *shell, t_command *cmd);

/*QUOTES*/
bool	s_out_q(char *s);
bool	d_out_q(char *s);
bool	even_q(char *s);
char	*rm_q(char *s);

/*EXIT*/
char	*check_exit(t_shell *shell, char **token);

#endif