#include "../../include/core/shell.h"

int main(int argc, const char **argv, const char **env)
{
	t_shell shell;

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
			shell.pipeline.num_commands = ft_list_size(&shell.pipeline.commands);
			execute(&shell); //, (char **) env); // will be replaced with shell env
		}
		if (errno)
		{
			perror("");
			printf("ERRNO: %d\n", errno);
		}
		if (errno == ENOMEM)
			error_exit(&shell, "malloc", ENOMEM);
		reset_shell(&shell);
		free((void *) input);
	}
}
