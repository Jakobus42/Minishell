#include "core/builtins/builtins.h"
#include <limits.h>

static char *trim_exit(char *s)
{
	char *tmp;
	char *tmp1;
	int   x;
	bool  flag;
	char *trim;

	tmp = NULL;
	if (s)
	{
		trim = ft_strtrim(s, " ");
		x = 0;
		flag = false;
		if (x == 0 && (trim[x] == '-' || trim[x] == '+'))
		{
			if (trim[x] == '-')
				flag = true;
			x++;
		}
		while (trim[x] && trim[x] == '0')
			x++;
		tmp = ft_substr(trim, x, ft_strlen(trim) - x);
		if (flag == true)
		{
			tmp1 = ft_strjoin_null("-", tmp);
			return (free_and_null((void **) &tmp), tmp1);
		}
		return (tmp);
	}
	return (NULL);
}

static unsigned long ft_atoul(const char *nptr)
{
	int           i;
	int           j;
	unsigned long nb;

	i = 0;
	j = 1;
	nb = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[0] == '+')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		nb = 10 * nb;
		nb = nptr[i] - 48 + nb;
		i++;
	}
	return (nb * j);
}

static char *exit_num_status(t_shell *shell, char *token)
{
	char	     *tmp;
	char	     *str;
	unsigned long ul;

	tmp = NULL;
	str = NULL;
	tmp = trim_exit(token);
	if (!tmp)
		return (shell->exec.exit = true, NULL);
	if (tmp[0] == '-')
		ul = ft_atoul(ft_substr(tmp, 1, ft_strlen(tmp)));
	else
		ul = ft_atoul(tmp);
	if (ft_strlen(tmp) > 20 || (tmp[0] != '-' && ul > LONG_MAX) || (tmp[0] == '-' && ul - 1 > LONG_MAX))
	{
		str = ft_strjoin_null("exit: ", ft_strjoin_null(token, ": numeric "
		                                                       "argument "
		                                                       "required"));
		shell->error_code = 2;
	}
	else
	{
		shell->error_code = (uint8_t) ft_atol(tmp);
		free_and_null((void **) &tmp);
	}
	if (!shell->pipeline.commands->next && shell->exec.exit_count == 1)
		return (shell->exec.exit = true, str);
	else
		return (shell->exec.exit = false, str);
}

static char *exit_non_numeric(t_shell *shell, char *token)
{
	char *str;

	str = NULL;
	str = ft_strjoin_null("exit: ", ft_strjoin_null(token, ": numeric argument "
	                                                       "required"));
	shell->error_code = 2;
	if (!shell->pipeline.commands->next && shell->exec.exit_count == 1)
		return (shell->exec.exit = true, str);
	return (shell->exec.exit = false, str);
}

char *check_exit(t_shell *shell, char **token)
{
	char *str;
	char *tmp;

	str = NULL;
	if (!ft_strcmp(token[0], "exit"))
	{
		shell->exec.exit_count++;
		if (!token[1] && !shell->pipeline.commands->next && shell->exec.exit_count == 1)
			return (shell->exec.exit = true, NULL);
		tmp = ft_strtrim(token[1], " ");
		if (tmp && !token[2] && (only_digits(tmp, 0) || ((tmp[0] == '+' || tmp[0] == '-') && only_digits(tmp, 1))))
			return (free_and_null((void **) &tmp), exit_num_status(shell, token[1]));
		else if (tmp && (!only_digits(tmp, 0) || (ft_isalpha(tmp[0]) || tmp[0] == '-' || tmp[0] == '+' || ft_strlen(tmp) == 0)))
			return (free_and_null((void **) &tmp), exit_non_numeric(shell, token[1]));
		else if (tmp && token[2])
		{
			str = ft_strdup("exit: too many arguments");
			return (free_and_null((void **) &tmp), shell->exec.exit = false,
			        shell->error_code = 1, str);
		}
	}
	return (shell->exec.exit = false, NULL);
}
