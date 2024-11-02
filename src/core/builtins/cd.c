#include "core/builtins/builtins.h"
#include <stdint.h>

static void	ft_chdir(char *target_dir, t_shell *shell)
{
	char	*current_pwd;

	current_pwd = getcwd(NULL, 0);
	if (!current_pwd)
		error_fatal(shell, "getcwd in chdir failed\n", MALLOC_FAIL);
	if (chdir(target_dir) != 0)
	{
		free_and_null((void **)&current_pwd);
		log_message(LOG_ERROR, "cd: %s: %s\n", target_dir, strerror(errno));
		shell->error_code = 1;
		return ;
	}
	if (set_env(shell, shell->env, "OLDPWD", current_pwd))
		return (free_and_null((void **)&current_pwd), perror("OLDPWD failed"));
	free_and_null((void **)&current_pwd);
	current_pwd = getcwd(NULL, 0);
	if (!current_pwd)
		error_fatal(shell, "getcwd in chdir failed\n", MALLOC_FAIL);
	if (set_env(shell, shell->env, "PWD", current_pwd))
		return (free_and_null((void **)&current_pwd), perror("PWD failed"));
	free_and_null((void **)&current_pwd);
}

void	cd_builtin(t_shell *shell)
{
	char		*home;
	t_command	*cmd;

	home = NULL;
	cmd = shell->pipeline.commands->content;
	if (cmd->argc > 2)
		return (shell->error_code = 2, log_message(LOG_ERROR,
				"cd: too many arguments\n"));
	if (!cmd->args[1])
	{
		home = get_env(shell, shell->env, "HOME");
		if (!home)
			return (shell->error_code = 1, log_message(LOG_ERROR,
					"cd: HOME not set\n"));
		return (ft_chdir(home, shell), free_and_null((void **)&home));
	}
	ft_chdir(cmd->args[1], shell);
}
