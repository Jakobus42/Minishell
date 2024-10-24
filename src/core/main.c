#include "../../include/core/shell.h"

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
		add_history(input);
		if (setup_pipeline(&shell, input) == 0)
		{
			if (VERBOSE)
				debug_print_pipeline(&shell.pipeline);
			execute_pipeline(&shell, (char **) env); // will be replaced with shell env
		}
		printf("ERRNO: %d\n", errno);
		if (errno == ENOMEM)
			error_exit(&shell, "malloc", ENOMEM);
		reset_shell(&shell);
		free((void *) input);
	}
}
