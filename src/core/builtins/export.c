/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 14:50:12 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/11/02 17:00:22 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/builtins/builtins.h"
#include "core/shell/shell.h"

static void	print_pair(t_pair *pair)
{
	if (pair->key && ft_strcmp(pair->key, "_"))
		ft_putstr_fd("declare -x ", 1);
	if (pair->key && ft_strlen(pair->value) > 0 && ft_strcmp(pair->key, "_"))
	{
		ft_putstr_fd(pair->key, 1);
		ft_putstr_fd("=\"", 1);
		ft_putstr_fd(pair->value, 1);
		ft_putendl_fd("\"", 1);
	}
	else if (ft_strcmp(pair->key, "_"))
		ft_putendl_fd(pair->key, 1);
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
	env_temp = convert_env_to_list(shell, (const char **)arr);
	free_array((void ***)&arr);
	cur = env_temp;
	while (cur)
	{
		pair = (t_pair *)cur->content;
		print_pair(pair);
		cur = cur->next;
	}
	ft_lstclear(&env_temp, &free_env);
}

char	**create_new_split(char **temp, int lim_pos, char *s)
{
	char	**new;

	new = NULL;
	new = ft_calloc(3, sizeof(char *));
	if (!new)
		return (free_and_null((void **)temp), NULL);
	new[0] = ft_strdup(*temp);
	if (!new[0])
		return (free_and_null((void **)temp), NULL);
	new[1] = ft_substr(s, lim_pos + 1, (ft_strlen(s) - lim_pos + 1));
	if (!new[1])
		return (free_and_null((void **)temp), free_array((void ***)&new), NULL);
	return (new);
}

char	**split_once(t_shell *shell, char *s, int lim)
{
	char	*temp;
	int		lim_pos;
	char	**new;

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
		new = create_new_split(&temp, lim_pos, s);
		if (!new)
			(free_and_null((void **)&temp), error_fatal(shell, "malloc",
					MALLOC_FAIL));
	}
	return (free_and_null((void **)&temp), new);
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
			free_array((void ***)&split);
		}
		else if (split[0] && split[1])
		{
			if (set_env(shell, shell->env, split[0], split[1]))
				return (free_array((void ***)&split), shell->error_code = 1,
					perror("set_env failed"));
			free_array((void ***)&split);
		}
		i++;
	}
}
