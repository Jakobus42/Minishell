#include "core/builtins/builtins.h"
#include "core/shell.h"

// TODO: Lilly :)

// Retrieves the value for the given key,returns NULL on failure
// TODO dont dup maybe
char *get_env(t_list *env, const char *key)
{
	char *value;

	value = NULL;
	while (env)
	{
		if (!ft_strcmp((char *) ((t_pair *) env->content)->key, key))
		{
			value = ft_strdup((char *) ((t_pair *) env->content)->value);
			break;
		}
		env = env->next;
	}
	return (value);
}

// Updates or adds a key-value pair, returns 1 on failure
bool set_env(t_list *env, char *key, char *value)
{
	t_pair *pair;
	t_list *cur;

	cur = env;
	while (cur)
	{
		if (!ft_strcmp((char *) ((t_pair *) cur->content)->key, key))
		{
			free((char *) ((t_pair *) cur->content)->value);
			((t_pair *) cur->content)->value = ft_strdup(value);
			if (!(char *) ((t_pair *) cur->content)->value)
				return (perror(value), true);
			return (false);
		}
		cur = cur->next;
	}
	pair = ft_calloc(1, sizeof(t_pair));
	pair->key = ft_strdup(key);
	pair->value = ft_strdup(value);
	ft_lstnew_add_back(&env, (void *) pair);
	return (false);
}

// Removes a key-value pair, returns 1 if the key cant be found
bool remove_env_pair(t_list *env, const char *key)
{
	t_list *env_temp;
	t_pair *pair;

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
				free_and_null((void **) &env_temp);
				return (false);
			}
		}
		env_temp = env_temp->next;
	}
	return (true);
}

// Converts the list to a char**, returns NULL on failure
char **convert_env_to_array(t_list *env)
{
	char  **converted_env;
	t_pair *pair;
	char   *s;
	int     i;

	converted_env = ft_calloc(ft_list_size(&env) + 1, sizeof(char *));
	if (!converted_env)
		return (perror("calloc"), NULL);
	i = 0;
	while (env)
	{
		pair = (t_pair *) env->content;
		s = ft_strjoin_null(pair->key, "=");
		converted_env[i] = ft_strjoin_null(s, pair->value);
		free_and_null((void **) &s);
		if (!converted_env[i])
			return (free_array((void ***) &converted_env), NULL);
		env = env->next;
		i++;
	}
	return (converted_env);
}

t_list *convert_env_to_list(const char **env)
{
	t_list *converted_env;
	t_pair *pair;
	t_list *node;
	int     i;

	converted_env = NULL;
	i = 0;
	while (env[i])
	{
		pair = create_pair(env[i], pair);
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
