#include "core/env/env.h"

// TODO: Lilly :)

// Retrieves the value for the given key,returns NULL on failure
char *get_env(t_list *env, const char *key)
{
	char *value;

	value = NULL;
	while (env)
	{
		if (ft_strcmp(env->content->key, key))
		{
			value = ft_strdup(env->content->value);
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
		if (ft_strcmp(env->content->key, key))
		{
			free(env->content->value);
			env->content->value = ft_strdup(value);
			if (!env->content->value)
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
}

// Converts the list to a char**, returns NULL on failure
char **convert_env_to_array(t_list *env)
{
	printf("[INFO] convert_env_to_array not implemented yet\n");
	char **converted_env = NULL;

	(void) env;
	return converted_env;
}

static t_pair *create_pair(const char *str)
{
	char *equal_sign = ft_strchr(str, '=');
	if (!equal_sign)
		return NULL;

	t_pair *pair = ft_calloc(sizeof(t_pair), 1);
	if (!pair)
		return (NULL);

	pair->key = ft_substr(str, 0, equal_sign - str);
	if (!pair->key)
		return (free(pair), NULL);

	pair->value = ft_substr(equal_sign + 1, 0, ft_strlen(equal_sign + 1));
	if (!pair->value)
		return (free(pair), free(pair->key), NULL);
	return pair;
}

t_list *convert_env_to_list(const char **env)
{
	t_list *converted_env = NULL;

	while (*env)
	{
		t_pair *pair = create_pair(*env);
		if (!pair)
			return NULL;
		t_list *node = ft_lstnew(pair);
		if (!node)
			return (free(pair), NULL);
		ft_lstadd_back(&converted_env, node);
		env++;
	}
	return converted_env;
}
