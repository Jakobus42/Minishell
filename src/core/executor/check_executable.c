#include "core/shell/shell.h"
#include <sys/dir.h>

bool check_permissions(t_shell *shell, char *cmd)
{
	DIR *dir;

	dir = opendir(cmd);
	if (dir)
	{
		(ft_putstr_fd(cmd, 2), ft_putendl_fd(": Is a directory", 2));
		shell->error_code = 126;
		return (false);
	}
	else if (cmd && access(cmd, F_OK))
	{
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd(": No such file or directory", 2);
		shell->error_code = 127;
		return (false);
	}
	else if (access(cmd, R_OK) || access(cmd, X_OK))
	{
		(ft_putstr_fd(cmd, 2), ft_putendl_fd(": Permission denied", 2));
		shell->error_code = 126;
		return (false);
	}
	return (true);
}

bool pre_executable_check(t_shell *shell, char *cmd)
{
	if (cmd && ft_strchr(cmd, '/') && !check_permissions(shell, cmd))
		return (false);
	if (cmd && !ft_strcmp(cmd, "~"))
		return (ft_putstr_fd(cmd, 2), ft_putendl_fd(": Is a directory", 2),
		        shell->error_code = 126, false);
	// if (cmd && !paths)
	// {
	// 	ft_putstr_fd(cmd, 2);
	// 	ft_putendl_fd(": No such file or directory", 2);
	// 	shell->error_code = 127;
	// 	return (false);
	// }
	if (!cmd || ft_strlen(cmd) == 0 || !ft_strcmp(cmd, ".") || !ft_strcmp(cmd, ".."))
	{
		(ft_putstr_fd(cmd, 2), ft_putendl_fd(": command not found", 2));
		shell->error_code = 127;
		return (false);
	}
	return (true);
}

char *is_executable(t_shell *shell, char *cmd)
{
	int    i;
	char  *executable;
	char  *part;
	char **paths;

	i = -1;
	part = get_env(shell->env, "PATH");
	paths = ft_split(part, ':');
	free_and_null((void **) &part);
	if (!pre_executable_check(shell, cmd))
		return (free_array((void ***) &paths), NULL);
	if (cmd && access(cmd, X_OK) == 0)
		return (free_array((void ***) &paths), cmd);
	while (cmd && paths && paths[++i])
	{
		executable = ft_strjoin_null(paths[i], "/");
		if (!executable)
			return (free(part), free_array((void ***) &paths), NULL);
		part = ft_strjoin_null(executable, cmd);
		free_and_null((void **) &executable);
		if (!part)
			return (free(part), free_array((void ***) &paths), NULL);
		else if (access(part, X_OK) == 0)
			return (free_array((void ***) &paths), part);
		free_and_null((void **) &part);
	}
	if (!paths || ft_strlen(paths[0]) == 0)
	{
		if (!ft_strchr(cmd, '/'))
		{
			ft_putstr_fd(cmd, 2);
			ft_putendl_fd(": No such file or directory", 2);
			shell->error_code = 127;
			return (false);
		}
		(ft_putstr_fd(cmd, 2), ft_putendl_fd(": Permission denied", 2));
		shell->error_code = 126;
		return (false);
	}
	free_array((void ***) &paths);
	log_message(LOG_ERROR, "%s: command not found\n", cmd);
	return (shell->error_code = 127, NULL);
}
