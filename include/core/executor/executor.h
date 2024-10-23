#ifndef EXECUTOR_H
#define EXECUTOR_H

typedef struct s_command t_command;

/*CHECK EXECUTABLE*/
bool  check_permissions(t_shell *shell, char *cmd);
bool  pre_executable_check(t_shell *shell, char **paths, char *cmd);
char *is_executable(t_shell *shell, char *cmd); //, char **env);

/*REDIRECTIONS*/
int  check_filein(t_command *exec_cmd);
int  check_fileout(t_command *exec_cmd);
void redirect(int *files, int storage, int *pipe_fd);

/*EXECUTOR*/
uint8_t execute_command(t_shell *shell, t_command *command, char **env);
void    execute_pipeline(t_shell *shell, char **env);
bool    ft_strcmp_bool(const char *s1, const char *s2);

/*BUILTINS*/
bool is_builtin(char *s);
// uint8_t	execute_builtin(t_shell *shell, t_command *cmd);

#endif // EXECUTOR_H