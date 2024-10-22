#include <shell.h>
#include <stdio.h>
#include <stdlib.h>

void setup_pseudo_input(t_shell *shell)
{
	shell->pipeline.commands = calloc(3, sizeof(t_command));

	for (int i = 0; i < 3; ++i)
	{
		shell->pipeline.commands[i].cmd = calloc(2, sizeof(char *));
	}
	shell->pipeline.commands[0].redir = calloc(1, sizeof(t_redirection));
	shell->pipeline.commands[0].redir->file_name = strdup("out");
	shell->pipeline.commands[0].redir->type = REDIR_OUTPUT;
	shell->pipeline.commands[0].cmd[0] = strdup("ls -la");
	shell->pipeline.commands[1].cmd[0] = strdup("echo Hello World");
	shell->pipeline.commands[2].cmd[0] = strdup("cat");
}

int main(int ac, char **av, char **env)
{
	t_shell shell;
	// char	**input;
	// int		i;

	ft_bzero(&shell, sizeof(t_shell));
	if (ac == 0 || !av)
		return (1);
	if (!env)
		return (ft_putendl_fd("Error: no env available", 2), 1);
	// i = 0;
	// while (av[i])
	// {
	// 	input = ft_split(av[i], '|');

	// }
}