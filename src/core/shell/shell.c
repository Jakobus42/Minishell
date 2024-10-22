#include "../../../include/core/shell.h"

void initialize_shell(t_shell *shell)
{
	ft_bzero(shell, sizeof(t_shell));
}

bool setup_pipeline(t_shell *shell, const char *input)
{
	t_token *token;

	(void) shell;
	while ((token = next_token(&input)))
	{
		free(token);
	}
	return SUCCESS;
}

void reset_shell(t_shell *shell)
{
	errno = 0;
	reset_pipeline(&shell->pipeline);
	reset_env(&shell->env);
	ft_bzero(shell, sizeof(t_shell));
}

void error_exit(t_shell *shell, const char *error_msg, uint8_t error_code)
{
	ft_putstr_fd("Minishell: ", 2);
	if (error_msg)
		perror(error_msg);
	reset_shell(shell);
	exit(error_code);
}