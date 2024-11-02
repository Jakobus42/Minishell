#include "core/shell/shell.h"
#include "core/shell/signal.h"

uint8_t g_signal = 0;

int main(int argc, const char **argv, const char **env)
{
	t_shell shell;

	(void)argc;
	(void)argv;
	if (!env || (env && !*env))
		return (log_message(LOG_FATAL, "enviorment is empty, cant start shell"), 1);
	initialize_shell(&shell, env);
	while (true)
	{
		handle_signal(&shell, MODE_INTERACTIVE);
		shell.input = readline(GREEN "shell<3 " RESET);
		if (!shell.input)
			error_fatal(&shell, NULL, shell.error_code);
		handle_signal(&shell, MODE_NON_INTERACTIVE);
		if(*shell.input)
			add_history(shell.input);
		shell.error_code = setup_pipeline(&shell, shell.input);
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
		reset_shell(&shell);
	}
}
