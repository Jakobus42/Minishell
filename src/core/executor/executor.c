#include "../../../include/core/shell.h"

int check_filein(t_command *exec_cmd)
{
	int            f_in;
	t_redirection *redirs;

	f_in = -1;
	while (exec_cmd->redir)
	{
		redirs = (t_redirection *) exec_cmd->redir->content;
		if ((redirs->type == REDIR_INPUT || redirs->type == REDIR_HEREDOC) &&
		    redirs->file_name)
		{
			if (f_in != -1)
				close(f_in);
			f_in = open(redirs->file_name, O_CREAT | O_RDONLY, 0644);
			if (f_in == -1 || access(redirs->file_name, R_OK))
				return (perror(redirs->file_name), -1);
		}
		exec_cmd->redir = exec_cmd->redir->next;
	}
	return (f_in);
}

int check_fileout(t_command *exec_cmd)
{
	int            f_out;
	t_redirection *redirs;

	f_out = -1;
	while (exec_cmd->redir)
	{
		redirs = (t_redirection *) exec_cmd->redir->content;
		if (redirs->type == REDIR_OUTPUT && redirs->file_name)
		{
			if (f_out != -1)
				close(f_out);
			f_out = open(redirs->file_name, O_CREAT | O_TRUNC | O_WRONLY, 0644);
			if (f_out == -1 || access(redirs->file_name, W_OK))
				return (perror(redirs->file_name), -1);
		}
		else if (redirs->type == REDIR_APPEND && redirs->file_name)
		{
			if (f_out != -1)
				close(f_out);
			f_out = open(redirs->file_name, O_CREAT | O_APPEND | O_RDWR, 0644);
			if (f_out == -1 || access(redirs->file_name, R_OK) || access(redirs->file_name, W_OK))
				return (perror(redirs->file_name), -1);
		}
		exec_cmd->redir = exec_cmd->redir->next;
	}
	return (f_out);
}

void redirect(int *files, int storage, int *pipe_fd)
{
	if (files[0] != -1)
	{
		if (dup2(files[0], STDIN_FILENO) == -1)
			return (perror("dup2 files[0] failed"));
		close(files[0]);
	}
	else if (storage >= 0)
	{
		if (dup2(storage, STDIN_FILENO) == -1)
			return (perror("dup2 storage failed"));
		close(storage);
	}
	if (files[1] != -1)
	{
		if (dup2(files[1], STDOUT_FILENO) == -1)
			return (perror("dup2 files[1] failed"));
		close(files[1]);
	}
	else if (pipe_fd[1] != -1)
	{
		close(pipe_fd[0]);
		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
			return (perror("dup2 pipe_fd[1] failed"));
		close(pipe_fd[1]);
	}
}

uint8_t execute_command(t_shell *shell, t_command *command, char **env)
{
	char *cmd;
	char *path;
	// char	**env;//TODO: convert/create char **env

	cmd = command->cmd;
	if (is_builtin(cmd))
		return (0);
	// return (execute_builtin(shell, command));
	else
	{
		path = is_executable(shell, cmd); //, env);
		if (!path)
			return (shell->error_code);
		return (shell->error_code = execve(path, command->args, env));
	}
}

bool is_builtin(char *s)
{
	if ((ft_strcmp_bool(s, "unset")) || (ft_strcmp_bool(s, "env")) || (ft_strcmp_bool(s, "export")) || (ft_strcmp_bool(s, "cd")) || (ft_strcmp_bool(s, "echo")) || (ft_strcmp_bool(s, "pwd")))
		return (true);
	return (false);
}

// uint8_t	execute_builtin(t_shell *shell, t_command *cmd)
// {
// 	(void *)shell;
// 	(void *)cmd;
// 	return (0);
// }

void execute_pipeline(t_shell *shell, char **env)
{
	t_command *cmds;
	int        files[2];
	int        storage;
	int        pipe_fd[2];
	int        i;

	cmds = (t_command *) shell->pipeline.commands->content;
	if (shell->pipeline.num_commands == 1 &&
	    is_builtin((char *) shell->pipeline.commands->content))
		return; // shell->error_code = execute_builtin(shell, cmds);
	else
	{
		i = 0;
		storage = -1;
		while (shell->pipeline.commands)
		{
			cmds = (t_command *) shell->pipeline.commands->content;
			files[0] = check_filein(cmds);
			files[1] = check_fileout(cmds);
			if (i > 0)
				storage = pipe_fd[0];
			if (pipe(pipe_fd) == -1)
				return (perror("pipe failed"));
			redirect(files, storage, pipe_fd);
			shell->error_code = execute_command(shell, cmds, env);
			shell->pipeline.commands = shell->pipeline.commands->next;
		}
	}
}

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

bool ft_strcmp_bool(const char *s1, const char *s2)
{
	size_t x;
	size_t len_s1;
	size_t len_s2;

	x = 0;
	if (!s1 || !s2)
		return (false);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	if (len_s1 != len_s2)
		return (false);
	while (s1[x] && s2[x] && s1[x] == s2[x])
		x++;
	if (x == len_s1)
		return (true);
	return (false);
}
