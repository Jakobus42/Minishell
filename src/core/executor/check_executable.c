#include "core/shell/shell.h"
#include <sys/dir.h>

static bool	check_permissions(t_shell *shell, char **paths, char *cmd)
{
	DIR	*dir;

	dir = opendir(cmd);
	if (dir)
	{
		log_message(LOG_ERROR, "%s: Is a directory\n", cmd);
		shell->error_code = 126;
		closedir(dir);
		return (false);
	}
	else if (cmd && paths && access(cmd, F_OK))
	{
		log_message(LOG_ERROR, "%s: No such file or directory\n", cmd);
		shell->error_code = 127;
		return (false);
	}
	else if (cmd && paths && (access(cmd, R_OK) || access(cmd, X_OK)))
	{
		log_message(LOG_ERROR, "%s: Permission denied\n", cmd);
		shell->error_code = 126;
		return (false);
	}
	return (true);
}

static bool	pre_executable_check(t_shell *shell, char **paths, char *cmd)
{
	if (cmd && ft_strchr(cmd, '/') && !check_permissions(shell, paths, cmd))
		return (false);
	if (!cmd || ft_strlen(cmd) == 0 || !ft_strcmp(cmd, ".") || !ft_strcmp(cmd,
			".."))
	{
		if (cmd && !ft_strcmp(cmd, "."))
			log_message(LOG_ERROR, ".: filename argument required\n");
		else if (cmd)
			log_message(LOG_ERROR, "%s: command not found\n", cmd);
		else
			log_message(LOG_ERROR, ": command not found\n");
		shell->error_code = 127;
		return (false);
	}
	return (true);
}

static char	*find_path(char *cmd, char **paths)
{
	char	*executable;
	char	*part;
	int		i;

	i = -1;
	while (cmd && paths && paths[++i])
	{
		executable = ft_strjoin_null(paths[i], "/");
		if (!executable)
			return (free(part), free_array((void ***)&paths), NULL);
		part = ft_strjoin_null(executable, cmd);
		free_and_null((void **)&executable);
		if (!part)
			return (free(part), free_array((void ***)&paths), NULL);
		else if (access(part, X_OK) == 0)
			return (free_array((void ***)&paths), part);
		free_and_null((void **)&part);
	}
	return (NULL);
}

static char	*check_paths(t_shell *shell, char *cmd)
{
	if (cmd && access(cmd, F_OK))
	{
		log_message(LOG_ERROR, "%s: No such file or directory\n", cmd);
		shell->error_code = 127;
		return (NULL);
	}
	log_message(LOG_ERROR, "%s: Permission denied\n", cmd);
	shell->error_code = 126;
	return (NULL);
}

char	*is_executable(t_shell *shell, char *cmd)
{
	char	*part;
	char	**paths;

	part = get_env(shell, shell->env, "PATH");
	paths = ft_split(part, ':');
	free_and_null((void **)&part);
	if (!pre_executable_check(shell, paths, cmd))
		return (free_array((void ***)&paths), NULL);
	if (cmd && access(cmd, X_OK) == 0)
		return (free_array((void ***)&paths), cmd);
	part = find_path(cmd, paths);
	if (part)
		return (part);
	if (!paths || ft_strlen(paths[0]) == 0)
		return (check_paths(shell, cmd));
	free_array((void ***)&paths);
	log_message(LOG_ERROR, "%s: command not found\n", cmd);
	return (shell->error_code = 127, NULL);
}
