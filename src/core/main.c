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
			error_fatal(&shell, NULL, shell.error_code);
		add_history(input);
		shell.error_code = setup_pipeline(&shell, input);
		if (shell.error_code == 0 && shell.pipeline.commands)
		{
			if (VERBOSE)
				debug_print_pipeline(&shell.pipeline);
			execute(&shell);
			if (shell.exec.exit == true)
				error_fatal(&shell, NULL, shell.error_code);
		}
		if (errno)
			log_message(LOG_INFO, "errno: %d\n", errno);
		log_message(LOG_INFO, "error_code: %d\n", shell.error_code);
		free((void *) input);
		reset_shell(&shell);
	}
}
