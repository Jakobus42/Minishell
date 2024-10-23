#include "../../../include/core/shell.h"

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
	else if (access(cmd, F_OK))
	{
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd(": No such file or directory", 2);
		shell->error_code = 127;
		return (false);
	}
	else if (access(cmd, R_OK))
	{
		(ft_putstr_fd(cmd, 2), ft_putendl_fd(": Permission denied", 2));
		shell->error_code = 126;
		return (false);
	}
	return (true);
}

bool pre_executable_check(t_shell *shell, char **paths, char *cmd)
{
	if (cmd && ft_strchr(cmd, '/') && !check_permissions(shell, cmd))
		return (false);
	if (cmd && ft_strcmp_bool(cmd, "~"))
		return (ft_putstr_fd(cmd, 2), ft_putendl_fd(": Is a directory", 2),
		        shell->error_code = 126, false);
	if (cmd && !paths)
	{
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd(": No such file or directory", 2);
		shell->error_code = 127;
		return (false);
	}
	if (ft_strlen(cmd) == 0)
	{
		(ft_putstr_fd(cmd, 2), ft_putendl_fd(": command not found", 2));
		shell->error_code = 127;
		return (false);
	}
	if (cmd && ft_strcmp_bool(cmd, "."))
		return (ft_putendl_fd(".: filename argument required", 2), shell->error_code = 127, false);
	return (true);
}

char *is_executable(t_shell *shell, char *cmd) //, char **env)
{
	int    i;
	char  *executable;
	char  *part;
	char **paths = ft_split(getenv("PATH"), ':');
	// char	**paths = ft_split(get_env(shell->env, "PATH"), ':');

	i = -1;
	if (!pre_executable_check(shell, paths, cmd))
		return (NULL);
	if (cmd && access(cmd, X_OK) == 0 && !ft_strcmp_bool(cmd, ".") && !ft_strcmp_bool(cmd, ".."))
		return (cmd);
	while (cmd && paths[++i] && !ft_strcmp_bool(cmd, ".") && !ft_strcmp_bool(cmd, ".."))
	{
		executable = ft_strjoin(paths[i], "/");
		if (!executable)
			return (NULL);
		part = ft_strjoin(executable, cmd);
		free(executable);
		if (!part)
			return (NULL);
		else if (access(part, X_OK) == 0)
			return (part);
		free(part);
	}
	(ft_putstr_fd(cmd, 2), ft_putendl_fd(": command not found", 2));
	return (shell->error_code = 127, NULL);
}
