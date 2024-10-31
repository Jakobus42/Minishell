/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 20:26:27 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/10/31 16:27:28 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/builtins/builtins.h"
#include "core/shell/shell.h"

bool	check_valid_export(char *s)
{
	size_t	i;

	i = 0;
	if (s && (ft_isalpha(s[i]) || s[i] == '_'))
	{
		i++;
		while (s[i] && (ft_isalnum(s[i]) || s[i] == '_'))
			i++;
		if (i == ft_strlen(s))
			return (true);
	}
	return (false);
}

void	print_export(t_shell *shell, t_list *env)
{
	t_list	*env_temp;
	t_list	*cur;
	t_pair	*pair;
	char	**arr;

	env_temp = env;
	arr = convert_env_to_array(shell, env);
	sort_arr(arr);
	env_temp = convert_env_to_list(shell, (const char **) arr);
	free_array((void ***) &arr);
	cur = env_temp;
	while (cur)
	{
		pair = (t_pair *) cur->content;
		if (pair->key && ft_strcmp(pair->key, "_"))
			ft_putstr_fd("declare -x ", 1);
		if (pair->key && ft_strlen(pair->value) > 0
			&& ft_strcmp(pair->key, "_"))
		{
			ft_putstr_fd(pair->key, 1);
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(pair->value, 1);
			ft_putendl_fd("\"", 1);
		}
		else if (ft_strcmp(pair->key, "_"))
			ft_putendl_fd(pair->key, 1);
		cur = cur->next;
	}
	ft_lstclear(&env_temp, &free_env);
}

int	find_char(char *s, int lim)
{
	int	i;

	i = -1;
	while (s && s[++i])
	{
		if (s[i] == lim)
			return (i);
	}
	return (i);
}

char	**split_once(t_shell *shell, char *s, int lim)
{
	char	**new;
	char	*temp;
	int		lim_pos;

	new = NULL;
	lim_pos = find_char(s, lim);
	if (lim_pos == -1)
		return (NULL);
	temp = ft_substr(s, 0, lim_pos);
	if (!temp)
		return (error_fatal(shell, "substr in split_once failed\n",
			MALLOC_FAIL), NULL);
	if (check_valid_export(temp))
	{
		new = ft_calloc(3, sizeof(char *));
		if (!new)
			return (free_and_null((void **) &temp), error_fatal(shell,
				"calloc in split_once failed\n", MALLOC_FAIL), NULL);
		new[0] = ft_strdup(temp);
		if (!new[0])
			return (free_and_null((void **) &temp), error_fatal(shell,
				"strdup in split_once failed\n", MALLOC_FAIL), NULL);
		new[1] = ft_substr(s, lim_pos + 1, (ft_strlen(s) - lim_pos + 1));
		if (!new[1])
			return (free_and_null((void **) &temp),
				free_array((void ***) &new), error_fatal(shell,
				"substr in split_once failed\n", MALLOC_FAIL), NULL);
	}
	return (free_and_null((void **) &temp), new);
}

void	set_export(t_shell *shell, t_command *cmd)
{
	char	**split;
	int		i;

	i = 1;
	while (cmd->args[i])
	{
		split = split_once(shell, cmd->args[i], '=');
		if (!split || ft_strlen(split[0]) == 0)
		{
			shell->error_code = 1;
			log_message(LOG_ERROR, "export: `%s': not a valid identifier\n",
				cmd->args[i]);
			free_array((void ***) &split);
		}
		else if (split[0] && split[1])
		{
			if (set_env(shell, shell->env, split[0], split[1]))
				return (free_array((void ***) &split), shell->error_code = 1,
					perror("set_env failed"));
			free_array((void ***) &split);
		}
		i++;
	}
}
