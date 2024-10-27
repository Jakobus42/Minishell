#include "core/shell/shell.h"
#include "libft/ft_printf_fd.h"

void error_exit(t_shell *shell, const char *error_msg, uint8_t error_code)
{
	if (error_msg)
		perror(error_msg);
	ft_lstclear(&shell->env, &free_env);
	reset_shell(shell);
	exit((int)error_code);
}