#include "core/shell/shell.h"

static void ft_chdir(char *target_dir, t_shell *shell)
{
	char *current_pwd;

	current_pwd = getcwd(NULL, 0);
	if (chdir(target_dir) != 0)
	{
		free(current_pwd);
		log_message(LOG_ERROR, "cd: %s: %s\n", target_dir, strerror(errno));
		shell->error_code = 1;
		return;
	}
	if (set_env(shell->env, "OLDPWD", current_pwd))
		return (free(current_pwd), perror("set_env OLDPWD failed"));
	free(current_pwd);
	current_pwd = getcwd(NULL, 0);
	if (set_env(shell->env, "PWD", current_pwd))
		return (free(current_pwd), perror("set_env PWD failed"));
	free(current_pwd);
}

u_int8_t cd_builtin(t_shell *shell)
{
	char      *home;
	t_command *cmd;

	home = NULL;
	cmd = shell->pipeline.commands->content;
	if (cmd->argc > 2)
		return (shell->error_code = 1, log_message(LOG_ERROR, "cd: too many arguments\n"), 2);
	if (!cmd->args[1])
	{
		home = get_env(shell->env, "HOME");
		if (!home)
			return (log_message(LOG_ERROR, "cd: HOME not set\n"), 1);
		return (ft_chdir(home, shell), free(home), shell->error_code);
	}
	if (!ft_strcmp(cmd->args[1], "-"))
	{
		char *old_pwd = get_env(shell->env, "OLDPWD");
		if (!old_pwd)
			return (log_message(LOG_ERROR, "cd: OLDPWD not set\n"), 1);
		ft_chdir(old_pwd, shell);
		char *pwd = get_env(shell->env, "PWD");
		ft_putendl_fd(pwd, 1);
		free(pwd);
		return (shell->error_code);
	}
	ft_chdir(cmd->args[1], shell);
	return (shell->error_code);
}