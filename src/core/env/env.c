#include "core/env/env.h"
#include "core/shell.h"

void construct_env(char **env, t_list *menv)
{
	char  **temp;
	t_pair *env_pair;
	int     i;
	t_list *list_tmp;

	i = 0;
	menv = NULL;
	while (env[i])
	{
		temp = NULL;
		temp = ft_split(env[i], '=');
		env_pair = ft_calloc(1, sizeof(t_pair));
		env_pair->key = temp[0];
		env_pair->value = temp[1];
		list_tmp = ft_lstnew((void *) env_pair);
		if (!list_tmp)
			return (perror("ft_lstnew"));
		ft_lstadd_back(&menv, list_tmp);
		free_array((void ***) &temp);
		i++;
	}
}

// TODO: Lilly :)

// Retrieves the value for the given key,returns NULL on failure
char *get_env(t_list *env, const char *key)
{
	printf("[INFO] get_env not implemented yet\n");
	char *value = NULL;

	(void) env;
	(void) key;
	return value;
}

// Updates or adds a key-value pair, returns 1 on failure
bool set_env(t_list *env, const char *key, const char *value)
{
	printf("[INFO] set_env not implemented yet\n");

	(void) key;
	(void) env;
	(void) value;
	return 0;
}

// Removes a key-value pair, returns 1 if the key cant be found
bool remove_env_pair(t_list *env, const char *key)
{
	printf("[INFO] remove_env_pair not implemented yet\n");

	(void) env;
	(void) key;
	return 0;
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
