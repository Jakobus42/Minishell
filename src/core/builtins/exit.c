#include "core/builtins/builtins.h"

static char	*trim_exit(char *s)
{
	char	*tmp;
	char	*tmp1;
	int		x;
	bool	flag;

	tmp = NULL;
	if (s)
	{
		x = 0;
		flag = false;
		if (x == 0 && (s[x] == '-' || s[x] == '+'))
		{
			if (s[x] == '-')
				flag = true;
			x++;
		}
		while (s[x] && s[x] == '0')
			x++;
		tmp = ft_substr(s, x, ft_strlen(s) - x);
		if (flag == true)
		{
			tmp1 = ft_strjoin_null("-", tmp);
			free_and_null((void **)&tmp);
			return (tmp1);
		}
		return (tmp);
	}
	return (NULL);
}

static char	*exit_num_status(t_shell *shell, char **token)
{
	char	*tmp;

	tmp = NULL;
	tmp = trim_exit(token[1]);
	if (!tmp)
		return (shell->exec.exit = true, NULL);
	shell->error_code = (uint8_t)ft_atol(tmp);
	free_and_null((void **) &tmp);
	if (!shell->pipeline.commands->next && shell->exec.exit_count == 1)
		return (shell->exec.exit = true, NULL);
	else
		return (shell->exec.exit = false, NULL);
}

static char	*exit_non_numeric(t_shell *shell, char **token)
{
	char	*str;

	str = NULL;
	if (ft_strlen(token[1]) == 0)
		str = ft_strdup("exit: numeric argument required");
	else
		str = ft_strjoin_null("exit: ",
				ft_strjoin_null(token[1], ": numeric argument required"));
	shell->error_code = 2;
	if (!shell->pipeline.commands->next && shell->exec.exit_count == 1)
		return (shell->exec.exit = true, str);
	return (shell->exec.exit = false, str);
}

char	*check_exit(t_shell *shell, char **token)
{
	char	*str;

	str = NULL;
	if (!ft_strcmp(token[0], "exit"))
	{
		shell->exec.exit_count++;
		if (!token[1] && !shell->pipeline.commands->next)
			return (shell->exec.exit = true, NULL);
		else if (token[1] && !token[2] && (ft_isdigit(token[1][0])
			|| ((token[1][0] == '+' || token[1][0] == '-')
			&& ft_isdigit(token[1][1]))))
			return (exit_num_status(shell, token));
		else if (token[1] && (ft_isalpha(token[1][0])
			|| token[1][0] == '-'
			|| token[1][0] == '+' || ft_strlen(token[1]) == 0))
			return (exit_non_numeric(shell, token));
		else if (token[1] && token[2])
		{
			str = ft_strdup("exit: too many arguments");
			return (shell->exec.exit = false, shell->error_code = 1, str);
		}
		else
			return (shell->exec.exit = false, NULL);
	}
	return (shell->exec.exit = false, NULL);
}
