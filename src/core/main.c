#include "core/shell/shell.h"

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
		{
			error_fatal(&shell, NULL, shell.error_code);
			return 1;
		}
		add_history(input);
		if (setup_pipeline(&shell, input) == 0)
		{
			if (VERBOSE)
				debug_print_pipeline(&shell.pipeline);
			shell.pipeline.num_commands = ft_list_size(&shell.pipeline.commands);
			execute(&shell);
		}
		if (errno)
			log_message(LOG_INFO, "errno: %d\n", errno);
		log_message(LOG_INFO, "error_code: %d\n", shell.error_code);
		free((void *) input);
		if (errno == ENOMEM) // TODO: cant do it like this
			error_fatal(&shell, "malloc", MALLOC_FAIL);
		reset_shell(&shell);
	}
}
