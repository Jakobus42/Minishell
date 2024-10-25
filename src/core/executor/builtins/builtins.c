#include "../../../../include/core/shell.h"

bool is_builtin(char *s)
{
	if (!ft_strcmp(s, "unset") || !ft_strcmp(s, "env") || !ft_strcmp(s, "export") || !ft_strcmp(s, "cd") || !ft_strcmp(s, "echo") || !ft_strcmp(s, "pwd"))
		return (true);
	return (false);
}

uint8_t execute_builtin(t_shell *shell, t_command *cmd)
{
	(void) shell;
	(void) cmd;
	return (0);
}
