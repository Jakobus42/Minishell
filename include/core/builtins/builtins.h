/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 14:45:48 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/11/02 14:45:49 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "core/shell/shell.h"

/*BUILTINS*/
bool			is_builtin(char *s);
void			which_builtin(t_shell *shell, t_command *cmd);
uint8_t			execute_single_builtin(t_shell *shell, t_command *cmd);

/*REDIRECT BUILTINS*/
void			reset_fds(int copy_stdin, int copy_stdout);
void			redirect_builtin(t_shell *shell);

/*CD*/
void			cd_builtin(t_shell *shell);

/*ECHO*/
int				echo(char **token);

/*EXPORT*/
bool			check_valid_export(char *s);
void			print_export(t_shell *shell, t_list *env);
int				find_char(char *s, int lim);
char			**split_once(t_shell *shell, char *s, int lim);
void			set_export(t_shell *shell, t_command *cmd);

/*EXPORT_UTILS*/
void			sort_arr(char **arr);
bool			check_valid_export(char *s);
int				find_char(char *s, int lim);

/*EXIT*/
unsigned long	ft_atoul(const char *nptr);
char			*check_exit(t_shell *shell, char **token);

/*EXIT UTILS*/
char			*final_trim_exit(t_shell *shell, bool flag, int x, char **trim);
unsigned long	get_atoul(char *tmp, t_shell *shell);
char			*exit_non_numeric_error(t_shell *shell, char *token);
char			*exit_too_many(char *str, t_shell *shell);
bool			only_digits(char *s, int start);

#endif