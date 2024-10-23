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
		if (!setup_pipeline(&shell, input))
		{
			if (VERBOSE)
				debug_print_pipeline(&shell.pipeline);
			execute_pipeline(&shell, (char **) env); // will be replaced with shell env
		}
		reset_shell(&shell);
		free((void *) input);
	}
}
