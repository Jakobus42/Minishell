#include "../../include/core/shell.h"

int main(int argc, const char **argv, const char **env)
{
	t_shell shell;
	pid_t  *pid;

	(void) argc;
	(void) argv;
	initialize_shell(&shell, env);
	while (true)
	{
		const char *input = readline(PROMPT);
		if (!input)
			error_exit(&shell, "readline", ERROR);
		add_history(input);
		if (setup_pipeline(&shell, input) == 0)
		{
			if (VERBOSE)
				debug_print_pipeline(&shell.pipeline);
			pid = ft_calloc(ft_list_size(&shell.pipeline.commands), sizeof(pid_t));
			execute_pipeline(&shell, pid, ft_list_size(&shell.pipeline.commands)); //, (char **) env); // will be replaced with shell env
		}
		printf("ERRNO: %d\n", errno);
		if (errno == ENOMEM)
			error_exit(&shell, "malloc", ENOMEM);
		reset_shell(&shell);
		free((void *) input);
	}
}
