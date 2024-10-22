#include "../../../include/core/shell.h"

void initialize_shell(t_shell *shell)
{
	ft_bzero(shell, sizeof(t_shell));
	// TODO: init env
}

void reset_shell(t_shell *shell)
{
	reset_pipeline(&shell->pipeline);
	reset_env(&shell->env);
	reset_tokens(&shell->tokens);
	ft_bzero(shell, sizeof(t_shell));
}

void error_exit(t_shell *shell, const char *error_msg, uint8_t error_code)
{
	ft_putstr_fd("Minishell: ", 2);
	if (error_msg)
	{
		perror(error_msg);
	}
	reset_shell(shell);
	exit(error_code);
}