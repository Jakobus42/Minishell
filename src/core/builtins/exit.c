/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 20:26:17 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/10/31 17:49:52 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/builtins/builtins.h"
#include <limits.h>

static char	*trim_exit(t_shell *shell, char *s)
{
	char	*tmp;
	char	*tmp1;
	int		x;
	bool	flag;
	char	*trim;

	tmp = NULL;
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
		tmp = ft_substr(trim, x, ft_strlen(trim) - x);
		free_and_null((void **)&trim);
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
	return (NULL);
}

static unsigned long	ft_atoul(const char *nptr)
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
	if (tmp[0] == '-')
	{
		str = ft_substr(tmp, 1, ft_strlen(tmp));
		if (!str)
			error_fatal(shell, "substr in exit_num_status failed\n", MALLOC_FAIL);
		ul = ft_atoul(str);
		free_and_null((void **)&str);
	}
	else
		ul = ft_atoul(tmp);
	if (ft_strlen(tmp) > 20 || (tmp[0] != '-' && ul > LONG_MAX)
		|| (tmp[0] == '-' && ul - 1 > LONG_MAX))
	{
		free_and_null((void **)&tmp);
		tmp = ft_strjoin_null(token, ": numeric argument required");
		if (!tmp)
			return (error_fatal(shell, "strjoin in exit non num failed\n", MALLOC_FAIL), NULL);
		str = ft_strjoin_null("exit: ", tmp);
		free_and_null((void **)&tmp);
		if (!str)
			return (error_fatal(shell, "strjoin in exit non num failed\n", MALLOC_FAIL), NULL);
		shell->error_code = 2;
	}
	else
	{
		shell->error_code = (uint8_t)ft_atol(tmp);
		free_and_null((void **) &tmp);
	}
	if (!shell->pipeline.commands->next && shell->exec.exit_count == 1)
		return (shell->exec.exit = true, str);
	else
		return (shell->exec.exit = false, str);
}

static char	*exit_non_numeric(t_shell *shell, char *token)
{
	char	*str;
	char	*temp;

	str = NULL;
	temp = ft_strjoin_null(token, ": numeric argument required");
	if (!temp)
		return (error_fatal(shell, "strjoin in exit non num failed\n", MALLOC_FAIL), NULL);
	str = ft_strjoin_null("exit: ", temp);
	free_and_null((void **)&temp);
	if (!str)
		return (error_fatal(shell, "strjoin in exit non num failed\n", MALLOC_FAIL), NULL);
	shell->error_code = 2;
	if (!shell->pipeline.commands->next && shell->exec.exit_count == 1)
		return (shell->exec.exit = true, str);
	return (shell->exec.exit = false, str);
}

char	*check_exit(t_shell *shell, char **token)
{
	char	*str;
	char	*tmp;

	str = NULL;
	if (!ft_strcmp(token[0], "exit"))
	{
		shell->exec.exit_count++;
		if (!token[1] && !shell->pipeline.commands->next
			&& shell->exec.exit_count == 1)
			return (shell->exec.exit = true, NULL);
		tmp = ft_strtrim(token[1], " ");
		if (!tmp)
			return (free_and_null((void **)&tmp), error_fatal(shell,
				"strtrim in check_exit failed\n", MALLOC_FAIL), NULL);
		if (tmp && !token[2] && (only_digits(tmp, 0)
				|| ((tmp[0] == '+' || tmp[0] == '-') && only_digits(tmp, 1))))
			return (free_and_null((void **) &tmp),
				exit_num_status(shell, token[1]));
		else if (tmp && (!only_digits(tmp, 0) || (ft_isalpha(tmp[0])
					|| tmp[0] == '-' || tmp[0] == '+' || ft_strlen(tmp) == 0)))
			return (free_and_null((void **) &tmp),
				exit_non_numeric(shell, token[1]));
		else if (tmp && token[2])
		{
			str = ft_strdup("exit: too many arguments");
			free_and_null((void **) &tmp);
			if (!str)
				error_fatal(shell, "strdup in check_exit failed\n", MALLOC_FAIL);
			return (shell->exec.exit = false, shell->error_code = 1, str);
		}
	}
	return (shell->exec.exit = false, NULL);
}
