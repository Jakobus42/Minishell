#include "core/builtins/builtins.h"
#include "core/env/env.h"
#include "core/shell/shell.h"

bool lst_del_node(t_list *list, t_pair *pair)
{
	t_list *temp;

	if (!list || !list->next || !pair)
		return (true);
	temp = list->next;
	list->next = list->next->next;
	free_pair(temp->content);
	free_and_null((void **) &temp);
	return (false);
}

void free_pair(t_pair *pair)
{
	free_and_null((void **) &pair->key);
	free_and_null((void **) &pair->value);
	free_and_null((void **) &pair);
}

t_pair *create_pair(const char *str, t_pair *pair)
{
	char **split;

	pair = ft_calloc(1, sizeof(t_pair));
	if (!pair)
		return (NULL);
	split = split_once((char *) str, '='); //
	if (!split)
		return (free_pair(pair), NULL);
	pair->key = ft_strdup(split[0]);
	if (!pair->key)
		return (free_array((void ***) &split), free_pair(pair), NULL);
	pair->value = ft_strdup(split[1]);
	if (!pair->key)
		return (free_array((void ***) &split), free_pair(pair), NULL);
	return (free_array((void ***) &split), pair);
}

bool valid_env(t_shell *shell, char *s)
{
	t_list *temp;
	t_pair *key;

	temp = shell->env;
	while (temp)
	{
		key = (t_pair *) temp->content;
		if (!ft_strcmp(key->key, s))
			return (true);
		temp = temp->next;
	}
	return (false);
}

void print_env(t_list *env)
{
	t_list *env_temp;
	t_pair *pair;

	env_temp = env;
	while (env_temp)
	{
		pair = (t_pair *) env_temp->content;
		if (pair->key)
		{
			ft_putstr_fd(pair->key, 1);
			ft_putstr_fd("=", 1);
			ft_putendl_fd(pair->value, 1);
		}
		env_temp = env_temp->next;
	}
}
