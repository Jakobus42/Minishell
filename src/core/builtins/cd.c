#include "core/shell/shell.h"

static void ft_chdir(char *target_dir, t_shell *shell)
{
	char *current_pwd;

	current_pwd = getcwd(NULL, 0);
	if (chdir(target_dir) != 0)
	{
		free(current_pwd);
		ft_putstr_fd("cd: ", 2);
		perror(target_dir);
		shell->error_code = 1;
		return;
	}
	if (set_env(shell->env, "OLDPWD", current_pwd))
		return (free(current_pwd), perror("set_env OLDPWD failed"));
	free(current_pwd);
	current_pwd = getcwd(NULL, 0);
	if (set_env(shell->env, "PWD", current_pwd))
		return (free(current_pwd), perror("set_env PWD failed"));
}

u_int8_t cd_builtin(t_shell *shell)
{
	char      *home;
	t_command *cmd;

	home = NULL;
	cmd = shell->pipeline.commands->content;
	if (cmd->argc > 2)
		return (ft_putendl_fd("cd: too many arguments", 2), 1);
	if (!cmd->args[1])
	{
		home = get_env(shell->env, "HOME");
		if (!home)
			return (ft_putendl_fd("cd: HOME not set", 2), 1);
		return (ft_chdir(home, shell), free(home), shell->error_code);
	}
	if (!ft_strcmp(cmd->args[1], "-"))
	{
		ft_chdir(get_env(shell->env, "OLDPWD"), shell);
		ft_putendl_fd(get_env(shell->env, "PWD"), 1);
		return (shell->error_code);
	}
	ft_chdir(cmd->args[1], shell);
	return (shell->error_code);
}