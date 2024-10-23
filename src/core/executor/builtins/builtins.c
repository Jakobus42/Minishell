#include "../../../../include/core/shell.h"

bool is_builtin(char *s)
{
	if ((ft_strcmp_bool(s, "unset")) || (ft_strcmp_bool(s, "env")) || (ft_strcmp_bool(s, "export")) || (ft_strcmp_bool(s, "cd")) || (ft_strcmp_bool(s, "echo")) || (ft_strcmp_bool(s, "pwd")))
		return (true);
	return (false);
}

// uint8_t	execute_builtin(t_shell *shell, t_command *cmd)
// {
// 	(void *)shell;
// 	(void *)cmd;
// 	return (0);
// }
