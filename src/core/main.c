#include "../../include/core/shell.h"
#include <stdio.h>

int main(int, char **, char **env)
{
	t_shell shell;

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
			// execute()
		}
		reset_shell(&shell);
	}
}