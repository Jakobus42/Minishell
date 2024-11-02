#include "core/builtins/builtins.h"
#include <limits.h>

static char	*trim_exit(t_shell *shell, char *s)
{
	int		x;
	bool	flag;
	char	*trim;

	if (s)
	{
		trim = ft_strtrim(s, " ");
		if (!trim)
			error_fatal(shell, "strtrim in trim_exit failed\n", MALLOC_FAIL);
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
		return (final_trim_exit(shell, flag, x, &trim));
	}
	return (NULL);
}

unsigned long	ft_atoul(const char *nptr)
{
	int				i;
	int				j;
	unsigned long	nb;

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

static char	*exit_non_numeric(t_shell *shell, char *token, char *str)
{
	char	*tmp;

	tmp = ft_strjoin_null(token, ": numeric argument required");
	if (!tmp)
		return (error_fatal(shell, "strjoin in exit non num failed\n",
				MALLOC_FAIL), NULL);
	str = ft_strjoin_null("exit: ", tmp);
	free_and_null((void **)&tmp);
	if (!str)
		return (error_fatal(shell, "strjoin in exit non num failed\n",
				MALLOC_FAIL), NULL);
	shell->error_code = 2;
	return (str);
}

static char	*exit_num_status(t_shell *shell, char *token)
{
	char			*tmp;
	char			*str;
	unsigned long	ul;

	tmp = NULL;
	str = NULL;
	tmp = trim_exit(shell, token);
	if (!tmp)
		return (shell->exec.exit = true, NULL);
	ul = get_atoul(tmp, shell);
	if (ft_strlen(tmp) > 20 || (tmp[0] != '-' && ul > LONG_MAX)
		|| (tmp[0] == '-' && ul - 1 > LONG_MAX))
		return (free_and_null((void **)&tmp), exit_non_numeric(shell, token,
				str));
	else
	{
		shell->error_code = (uint8_t)ft_atol(tmp);
		free_and_null((void **)&tmp);
	}
	if (!shell->pipeline.commands->next && shell->exec.exit_count == 1)
		return (shell->exec.exit = true, str);
	else
		return (shell->exec.exit = false, str);
}

char	*check_exit(t_shell *shell, char **token)
{
	char	*str;
	char	*tmp;

	str = NULL;
	shell->exec.exit_count++;
	if (!token[1] && !shell->pipeline.commands->next
		&& shell->exec.exit_count == 1)
		return (shell->exec.exit = true, NULL);
	tmp = ft_strtrim(token[1], " ");
	if (!tmp)
		return (free_and_null((void **)&tmp), error_fatal(shell,
				"strtrim in check_exit failed\n", MALLOC_FAIL), NULL);
	if (tmp && !token[2] && (only_digits(tmp, 0) || ((tmp[0] == '+'
					|| tmp[0] == '-') && only_digits(tmp, 1))))
		return (free_and_null((void **)&tmp), exit_num_status(shell, token[1]));
	else if (tmp && (!only_digits(tmp, 0) || (ft_isalpha(tmp[0])
				|| tmp[0] == '-' || tmp[0] == '+' || ft_strlen(tmp) == 0)))
		return (free_and_null((void **)&tmp), exit_non_numeric_error(shell,
				token[1]));
	else if (tmp && token[2])
		return (free_and_null((void **)&tmp), exit_too_many(str, shell));
	return (shell->exec.exit = false, NULL);
}
