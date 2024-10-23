#include "../../include/core/shell.h"
#include <stdio.h>

int main(int argc, const char **argv, const char **env)
{
	t_shell shell;
	t_list *menv;
	char  **env_arr;

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
			// execute()
		}
		menv = convert_env_to_list(env);
		env_arr = convert_env_to_array(menv);
		ft_print_array(env_arr);
		reset_shell(&shell);
		free((void *) input);
	}
}