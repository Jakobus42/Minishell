#include "core/builtins/builtins.h"
#include "core/shell/shell.h"

// TODO: Lilly :)

void free_pair(t_pair *pair)
{
	free_and_null((void **) &pair->key);
	free_and_null((void **) &pair->value);
	free_and_null((void **) &pair);
}

int get_valid_key_size(const char *key)
{
	const char *start = key;

	if (!ft_isalpha(*key) && *key != '_')
		return 0;
	key++;
	while (*key && (ft_isalnum(*key) || *key == '_'))
	{
		key++;
	}
	return key - start;
}

// Retrieves the value for the given key,returns NULL on failure
// TODO dont dup maybe
char *get_env(t_list *env, const char *key)
{
	char *value;

	value = NULL;
	while (env)
	{
		if (key && ft_strcmp((char *) ((t_pair *) env->content)->key, key) == 0)
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
	t_pair *pair;
	t_list *cur;

	cur = env;
	while (cur)
	{
		if (!ft_strcmp((char *) ((t_pair *) cur->content)->key, key))
		{
			if (check_valid_export(key, value))
				return (true);
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
	if (check_valid_export(key, value))
		return (free_pair(pair), true);
	ft_lstnew_add_back(&env, (void *) pair);
	return (false);
}

// Removes a key-value pair, returns 1 if the key cant be found
bool remove_env_pair(t_list *env, const char *key)
{
	t_list *env_temp;
	t_list *temp;
	t_pair *pair;

	env_temp = env;
	while (env_temp)
	{
		if (env_temp->next)
		{
			pair = (t_pair *) env_temp->next->content;
			if (!ft_strcmp(pair->key, key) && ft_strcmp(pair->key, "_"))
			{
				temp = env_temp->next;
				env_temp->next = env_temp->next->next;
				free_pair(temp->content);
				free_and_null((void **) &temp);
				return (false);
			}
		}
		else if (!env_temp->next)
		{
			pair = (t_pair *) env_temp->content;
			if (!ft_strcmp(pair->key, key) && ft_strcmp(pair->key, "_"))
			{
				free_pair(env_temp->content);
				free_and_null((void **) &env_temp);
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

static t_pair *create_pair(const char *str, t_pair *pair)
{
	char **split;

	pair = ft_calloc(1, sizeof(t_pair));
	if (!pair)
		return (NULL);
	split = ft_split(str, '=');
	if (!split)
		return (free(pair), NULL);
	pair->key = ft_strdup(split[0]);
	if (!pair->key)
		return (free_array((void ***) &split), free(pair), NULL);
	pair->value = ft_strdup(split[1]);
	if (!pair->key)
		return (free_array((void ***) &split), free(pair->key), free(pair), NULL);
	return (free_array((void ***) &split), pair);
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
