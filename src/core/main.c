#include "core/shell/shell.h"

uint8_t g_signal = 0;

int main(int argc, const char **argv, const char **env)
{
	t_shell shell;

	if (!env || (env && !*env))
		return (log_message(LOG_FATAL, "enviorment is empty, cant start shell"), 1);
	initialize_shell(&shell, argc, argv, env);
	run_shell(&shell);
}
