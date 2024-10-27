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
			execute(&shell);
			if (shell.exec.exit == true)
				error_exit(&shell, NULL, shell.error_code);
			if (errno)
				log_message(LOG_INFO, "errno: %d\n", errno);
			if (shell.error_code)
				log_message(LOG_INFO, "error_code: %d\n", shell.error_code);
		}
		free((void *) input);
		if (errno == ENOMEM) // TODO: cant do it like this
			error_exit(&shell, "malloc", ENOMEM);
		reset_shell(&shell);
	}
}
