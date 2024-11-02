#include "core/builtins/builtins.h"
#include <limits.h>

char	*final_trim_exit(t_shell *shell, bool flag, int x, char **trim)
{
	char	*tmp;
	char	*tmp1;

	tmp = NULL;
	tmp = ft_substr(*trim, x, ft_strlen(*trim) - x);
	free_and_null((void **)trim);
	if (!tmp)
		error_fatal(shell, "strdup in trim_exit failed\n", MALLOC_FAIL);
	if (flag == true)
	{
		tmp1 = ft_strjoin_null("-", tmp);
		free_and_null((void **)&tmp);
		if (!tmp1)
			error_fatal(shell, "strjoin in trim_exit failed\n", MALLOC_FAIL);
		return (tmp1);
	}
	return (tmp);
}

unsigned long	get_atoul(char *tmp, t_shell *shell)
{
	char			*str;
	unsigned long	ul;

	if (tmp[0] == '-')
	{
		str = ft_substr(tmp, 1, ft_strlen(tmp));
		if (!str)
			error_fatal(shell, "substr in exit_num_status failed\n",
				MALLOC_FAIL);
		ul = ft_atoul(str);
		free_and_null((void **)&str);
	}
	else
		ul = ft_atoul(tmp);
	return (ul);
}

char	*exit_non_numeric_error(t_shell *shell, char *token)
{
	char	*str;
	char	*temp;

	str = NULL;
	temp = ft_strjoin_null(token, ": numeric argument required");
	if (!temp)
		return (error_fatal(shell, "strjoin in exit non num failed\n",
				MALLOC_FAIL), NULL);
	str = ft_strjoin_null("exit: ", temp);
	free_and_null((void **)&temp);
	if (!str)
		return (error_fatal(shell, "strjoin in exit non num failed\n",
				MALLOC_FAIL), NULL);
	shell->error_code = 2;
	if (!shell->pipeline.commands->next && shell->exec.exit_count == 1)
		return (shell->exec.exit = true, str);
	return (shell->exec.exit = false, str);
}

char	*exit_too_many(char *str, t_shell *shell)
{
	str = ft_strdup("exit: too many arguments");
	if (!str)
		error_fatal(shell, "strdup in check_exit failed\n", MALLOC_FAIL);
	return (shell->exec.exit = false, shell->error_code = 1, str);
}

bool	only_digits(char *s, int start)
{
	if (!s || !s[start])
		return (false);
	while (s[start])
	{
		if (s[start] >= '0' && s[start] <= '9')
			start++;
		else
			return (false);
	}
	return (true);
}
