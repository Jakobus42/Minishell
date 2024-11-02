#include "core/builtins/builtins.h"
#include "core/parser/parser.h"
#include "core/shell/shell.h"

bool	is_builtin(char *s)
{
	if (!ft_strcmp(s, "unset") || !ft_strcmp(s, "env") || !ft_strcmp(s,
			"export") || !ft_strcmp(s, "cd") || !ft_strcmp(s, "echo")
		|| !ft_strcmp(s, "pwd") || !ft_strcmp(s, "exit"))
		return (true);
	return (false);
}

static void	builtin_pwd(t_shell *shell)
{
	char	*temp;

	temp = getcwd(NULL, 0);
	if (!temp)
		error_fatal(shell, "getcwd in which_builtin failed\n", MALLOC_FAIL);
	if (temp)
		ft_putendl_fd(temp, 1);
	free_and_null((void **)&temp);
}

void	which_builtin(t_shell *shell, t_command *cmd)
{
	char	**args;
	int		i;

	if (!ft_strcmp(cmd->args[0], "echo"))
		echo(cmd->args);
	else if (!ft_strcmp(cmd->args[0], "env"))
		print_env(shell->env);
	else if (!ft_strcmp(cmd->args[0], "pwd"))
		builtin_pwd(shell);
	else if (!ft_strcmp(cmd->args[0], "export") && !cmd->args[1])
		print_export(shell, shell->env);
	else if (!ft_strcmp(cmd->args[0], "export") && cmd->args[1])
		set_export(shell, cmd);
	else if (!ft_strcmp(cmd->args[0], "unset") && cmd->args[1])
	{
		i = 0;
		args = cmd->args;
		while (args[++i])
			remove_env_pair(shell->env, args[i]);
	}
	else if (!ft_strcmp(cmd->args[0], "cd"))
		cd_builtin(shell);
	else if (!ft_strcmp(cmd->args[0], "exit"))
		check_exit(shell, cmd->args);
}

uint8_t	execute_single_builtin(t_shell *shell, t_command *cmd)
{
	int	copy_stdin;
	int	copy_stdout;

	copy_stdin = dup(STDIN_FILENO);
	if (copy_stdin == -1)
		return (perror("dup copy_stdin failed"), 1);
	copy_stdout = dup(STDOUT_FILENO);
	if (copy_stdout == -1)
		return (close(copy_stdin), perror("dup copy_stdout failed"), 1);
	check_files(shell, cmd->redirs);
	if (shell->exec.infile == -1 || shell->exec.outfile == -1)
		return (reset_fds(copy_stdin, copy_stdout), close_fds(&shell->exec), 1);
	redirect_builtin(shell);
	which_builtin(shell, cmd);
	if (shell->exec.infile)
		close(shell->exec.infile);
	if (shell->exec.outfile)
		close(shell->exec.outfile);
	reset_fds(copy_stdin, copy_stdout);
	return (0);
}
