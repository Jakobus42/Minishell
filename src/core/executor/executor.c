#include "../../../include/core/shell.h"

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
