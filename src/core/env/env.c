#include "../../../include/core/env/env.h"

// TODO: Lilly :)

// Retrieves the value for the given key,returns NULL on failure
char *get_env(t_list *env, const char *key)
{
	char *value;

	value = NULL;
	while (env)
	{
		if (ft_strcmp((char *) ((t_pair *) env->content)->key, key))
		{
			value = ft_strdup((char *) ((t_pair *) env->content)->value);
			break;
		}
		env = env->next;
	}
	return (value);
}

// Updates or adds a key-value pair, returns 1 on failure
bool set_env(t_list *env, const char *key, const char *value)
{
	t_list *new;
	t_pair *pair;

	while (env)
	{
		if (ft_strcmp((char *) ((t_pair *) env->content)->key, key))
		{
			free((char *) ((t_pair *) env->content)->value);
			((t_pair *) env->content)->value = ft_strdup(value);
			if (!(char *) ((t_pair *) env->content)->value)
				return (perror(value), false);
			return (true);
		}
		env = env->next;
	}
	pair = ft_calloc(1, sizeof(t_pair *));
	pair->key = ft_strdup(key);
	pair->value = ft_strdup(value);
	new = ft_calloc(1, sizeof(t_list *));
	new = ft_lstnew((void *) pair);
	ft_lstadd_back(&env, new);
	return (true);
}

// Removes a key-value pair, returns 1 if the key cant be found
bool remove_env_pair(t_list *env, const char *key)
{
	while (env)
	{
		if (env->next && ft_strcmp((char *) ((t_pair *) env->next->content)->key, key))
		{
			free_and_null((void **) env->next);
			if (env->next->next)
				env->next = env->next->next;
			else
				env->next = NULL;
			return (true);
		}
		env = env->next;
	}
	return (false);
}

// Converts the list to a char**, returns NULL on failure
char **convert_env_to_array(t_list *env)
{
	char **converted_env;
	char  *s;
	char  *s1;
	int    i;

	converted_env = ft_calloc(ft_list_size(&env) + 1, sizeof(char *));
	if (!converted_env)
		return (perror("calloc"), NULL);
	i = 0;
	while (env)
	{
		if ((char *) ((t_pair *) env->content)->key &&
		    ft_strlen((char *) ((t_pair *) env->content)->key) > 0)
		{
			s = ft_strjoin((char *) ((t_pair *) env->content)->key, "=\"");
			s1 = ft_strjoin(s, (char *) ((t_pair *) env->content)->value);
			converted_env[i] = ft_strjoin(s1, "\"");
			free_and_null((void **) s);
			free_and_null((void **) s1);
		}
		else
			converted_env[i] = ft_strdup((char *) ((t_pair *) env->content)->key);
		env = env->next;
		i++;
	}
	return (converted_env);
}

static t_pair *create_pair(const char *str)
{
	t_pair *pair;
	char  **split;

	pair = ft_calloc(sizeof(t_pair), 1);
	if (!pair)
		return (NULL);
	split = ft_split(str, '=');
	pair->key = ft_strdup(split[0]);
	if (!pair->key)
		return (free_array((void ***) split), free(pair), NULL);
	if (split[1])
	{
		pair->value = ft_strdup(split[1]);
		if (!pair->value)
			return (free_array((void ***) split), free(pair), free(pair->key), NULL);
	}
	return (free_array((void ***) split), pair);
}

t_list *convert_env_to_list(const char **env)
{
	t_list *converted_env;
	t_pair *pair;
	t_list *node;

	converted_env = NULL;
	while (*env)
	{
		pair = create_pair(*env);
		if (!pair)
			return (NULL);
		node = ft_lstnew(pair);
		if (!node)
			return (free(pair), NULL);
		ft_lstadd_back(&converted_env, node);
		env++;
	}
	return (converted_env);
}
