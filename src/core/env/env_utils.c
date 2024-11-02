/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 14:50:23 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/11/02 16:06:06 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/builtins/builtins.h"
#include "core/env/env.h"
#include "core/shell/shell.h"

bool	lst_del_node(t_list *list, t_pair *pair)
{
	t_list	*temp;

	if (!list || !list->next || !pair)
		return (true);
	temp = list->next;
	list->next = list->next->next;
	free_pair(temp->content);
	free_and_null((void **)&temp);
	return (false);
}

void	free_pair(t_pair *pair)
{
	free_and_null((void **)&pair->key);
	free_and_null((void **)&pair->value);
	free_and_null((void **)&pair);
}

t_pair *create_pair(const char *str)
{
	char *equal_sign = ft_strchr(str, '=');
	if (!equal_sign)
		return NULL;
	t_pair *pair = ft_calloc(sizeof(t_pair), 1);
	if (!pair)
		return (NULL);
	pair->key = ft_substr(str, 0, (size_t) (equal_sign - str));
	if (!pair->key)
		return (free(pair), NULL);
	pair->value = ft_substr(equal_sign + 1, 0, ft_strlen(equal_sign + 1));
	if (!pair->value)
		return (free(pair->key), free(pair), NULL);
	return pair;
}

bool	valid_env(t_shell *shell, char *s)
{
	t_list	*temp;
	t_pair	*key;

	temp = shell->env;
	while (temp)
	{
		key = (t_pair *)temp->content;
		if (!ft_strcmp(key->key, s))
			return (true);
		temp = temp->next;
	}
	return (false);
}

void	print_env(t_list *env)
{
	t_list	*env_temp;
	t_pair	*pair;

	env_temp = env;
	while (env_temp)
	{
		pair = (t_pair *)env_temp->content;
		if (pair->key)
		{
			ft_putstr_fd(pair->key, 1);
			ft_putstr_fd("=", 1);
			ft_putendl_fd(pair->value, 1);
		}
		env_temp = env_temp->next;
	}
}
