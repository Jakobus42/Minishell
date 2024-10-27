#include "core/shell/shell.h"

void error_fatal(t_shell *shell, const char *msg, uint8_t error_code)
{
	ft_lstclear(&shell->env, &free_env);
	if (msg)
		log_message(LOG_FATAL, "%s: %s", msg, strerror(errno));
	reset_shell(shell);
	exit(error_code);
}