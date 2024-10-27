#include "core/builtins/builtins.h"
#include "core/parser/parser.h"
#include "core/shell.h"

bool is_builtin(char *s)
{
	if (!ft_strcmp(s, "unset") || !ft_strcmp(s, "env") || !ft_strcmp(s, "export") || !ft_strcmp(s, "cd") || !ft_strcmp(s, "echo") || !ft_strcmp(s, "pwd") || !ft_strcmp(s, "exit"))
		return (true);
	return (false);
}

void reset_fds(int copy_stdin, int copy_stdout)
{
	if (copy_stdin != -1)
	{
		if (dup2(STDIN_FILENO, copy_stdin) == -1)
			return (perror("dup2 reset stdin failed"));
		close(copy_stdin);
	}
	if (copy_stdout != -1)
	{
		if (dup2(STDIN_FILENO, copy_stdout) == -1)
			return (perror("dup2 reset stdout failed"));
		close(copy_stdout);
	}
}

void redirect_builtin(t_shell *shell)
{
	if (shell->exec.infile != -1)
	{
		if (dup2(shell->exec.infile, STDIN_FILENO) == -1)
			return (perror("dup2 single_builtin infile failed"));
		close(shell->exec.infile);
	}
	if (shell->exec.outfile != -1)
	{
		if (dup2(shell->exec.outfile, STDOUT_FILENO) == -1)
			return (perror("dup2 single_builtin fileout failed"));
		close(shell->exec.outfile);
	}
}

void which_builtin(t_shell *shell, t_command *cmd)
{
	char 	*temp;

	if (!ft_strcmp(cmd->args[0], "echo"))
		echo(cmd->args);
	else if (!ft_strcmp(cmd->args[0], "env"))
		print_env(shell->env);
	else if (!ft_strcmp(cmd->args[0], "pwd"))
	{
		temp = getcwd(NULL, 0);
		ft_putendl_fd(temp, 2);
		free(temp);
	}
	else if (!ft_strcmp(cmd->args[0], "export") && !cmd->args[1])
		print_export(shell->env);
	else if (!ft_strcmp(cmd->args[0], "export") && cmd->args[1])
		set_export(shell, cmd);
	else if (!ft_strcmp(cmd->args[0], "unset") && cmd->args[1])
	{
		if (remove_env_pair(shell->env, cmd->args[1]))
			perror("remove_env_pair failed");
	}
	else if (!ft_strcmp(cmd->args[0], "cd"))
		shell->error_code = cd_builtin(shell);
	else if (!ft_strcmp(cmd->args[0], "exit"))
		check_exit(shell, cmd->args);
}

uint8_t execute_single_builtin(t_shell *shell, t_command *cmd)
{
	int copy_stdin;
	int copy_stdout;

	copy_stdin = dup(STDIN_FILENO);
	if (copy_stdin == -1)
		return (perror("dup copy_stdin failed"), 1);
	copy_stdout = dup(STDOUT_FILENO);
	if (copy_stdout == -1)
		return (perror("dup copy_stdout failed"), 1);
	shell->exec.infile = check_filein(cmd->redirs);
	shell->exec.outfile = check_fileout(cmd->redirs);
	redirect_builtin(shell);
	which_builtin(shell, cmd);
	reset_fds(copy_stdin, copy_stdout);
	return (0);
}
