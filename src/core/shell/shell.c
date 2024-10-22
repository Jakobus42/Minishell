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