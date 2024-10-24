#include "../../include/core/shell.h"
#include <stdio.h>

int main(int argc, const char **argv, const char **env)
{
	t_shell shell;
	char  **env_arr;

	(void) argc;
	(void) argv;
	initialize_shell(&shell, env);
	env_arr = convert_env_to_array(shell.env.data);
	ft_print_array(env_arr);
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
		free((void *) input);
	}
}
