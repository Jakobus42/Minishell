/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 20:26:40 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/10/31 16:34:14 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/builtins/builtins.h"
#include "core/shell/shell.h"

int	get_valid_key_size(const char *key)
{
	const char	*start;

	start = key;
	if (!ft_isalpha(*key) && *key != '_')
		return (0);
	key++;
	while (*key && (ft_isalnum(*key) || *key == '_'))
	{
		key++;
	}
	return (key - start);
}

char	*get_env(t_shell *shell, t_list *env, const char *key)
{
	char	*value;

	value = NULL;
	while (env)
	{
		if (key && !ft_strcmp((char *)((t_pair *) env->content)->key, key))
		{
			value = ft_strdup((char *)((t_pair *) env->content)->value);
			if (!value)
				error_fatal(shell, "strdup in get_env failed\n", MALLOC_FAIL);
			break ;
		}
		env = env->next;
	}
	return (value);
}

bool	set_env(t_shell *shell, t_list *env, char *key, char *value)
{
	t_pair	*pair;
	t_list	*cur;

	cur = env;
	while (cur)
	{
		if (!ft_strcmp((char *)((t_pair *) cur->content)->key, key))
		{
			free_and_null((void **)&(((t_pair *) cur->content)->value));
			((t_pair *) cur->content)->value = ft_strdup(value);
			if (!(char *)((t_pair *) cur->content)->value)
				error_fatal(shell, "strdup in set_env failed\n", MALLOC_FAIL);
			return (false);
		}
		cur = cur->next;
	}
	pair = ft_calloc(1, sizeof(t_pair));
	if (!pair)
		error_fatal(shell, "calloc in set_env failed\n", MALLOC_FAIL);
	pair->key = ft_strdup(key);
	if (!pair->key)
		error_fatal(shell, "strdup in set_env failed\n", MALLOC_FAIL);
	pair->value = ft_strdup(value);
	if (!pair->value)
		error_fatal(shell, "strdup in set_env failed\n", MALLOC_FAIL);
	ft_lstnew_add_back(&env, (void *)pair);
	return (false);
}

bool	remove_env_pair(t_list *env, const char *key)
{
	t_list	*env_temp;
	t_pair	*pair;

	env_temp = env;
	while (env_temp)
	{
		if (env_temp->next)
		{
			pair = (t_pair *) env_temp->next->content;
			if (!ft_strcmp(pair->key, key) && ft_strcmp(pair->key, "_"))
				return (lst_del_node(env_temp, pair));
		}
		else
		{
			pair = (t_pair *) env_temp->content;
			if (!ft_strcmp(pair->key, key) && ft_strcmp(pair->key, "_"))
			{
				free_pair(env_temp->content);
				free_and_null((void **)&env_temp);
				return (false);
			}
		}
		env_temp = env_temp->next;
	}
	return (true);
}

char	**convert_env_to_array(t_shell *shell, t_list *env)
{
	char	**converted_env;
	t_pair	*pair;
	char	*s;
	int		i;

	converted_env = ft_calloc(ft_list_size(&env) + 1, sizeof(char *));
	if (!converted_env)
		error_fatal(shell, "calloc in conv env to arr failed\n", MALLOC_FAIL);
	i = 0;
	while (env)
	{
		pair = (t_pair *) env->content;
		s = ft_strjoin_null(pair->key, "=");
		if (!s)
			return (error_fatal(shell, "strdup in conv env to arr failed\n", MALLOC_FAIL),
				free_array((void ***)&converted_env), NULL);
		converted_env[i] = ft_strjoin_null(s, pair->value);
		free_and_null((void **) &s);
		if (!converted_env[i])
			return (free_array((void ***) &converted_env),
				error_fatal(shell, "strjoin in conv env to arr failed\n",
				MALLOC_FAIL), NULL);
		env = env->next;
		i++;
	}
	return (converted_env);
}

t_list	*convert_env_to_list(t_shell *shell, const char **env)
{
	t_list	*converted_env;
	t_pair	*pair;
	t_list	*node;
	int		i;

	converted_env = NULL;
	i = 0;
	while (env[i])
	{
		pair = create_pair(shell, env[i], pair);
		if (!pair)
			return (NULL);
		node = ft_lstnew(pair);
		if (!node)
			return (free_pair(pair), NULL);
		ft_lstadd_back(&converted_env, node);
		i++;
	}
	return (converted_env);
}
