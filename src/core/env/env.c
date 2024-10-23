#include "core/env/env.h"

// TODO: Lilly :)

// Retrieves the value for the given key,returns NULL on failure
char *get_env(t_list *env, const char *key)
{
	printf("[INFO] get_env not implemented yet");
	char *value = NULL;

	(void) env;
	(void) key;
	return value;
}

// Updates or adds a key-value pair, returns 1 on failure
bool set_env(t_list *env, const char *key, const char *value)
{
	printf("[INFO] set_env not implemented yet");

	(void) key;
	(void) env;
	(void) value;
	return 0;
}

// Removes a key-value pair, returns 1 if the key cant be found
bool remove_env_pair(t_list *env, const char *key)
{
	printf("[INFO] remove_env_pair not implemented yet");

	(void) env;
	(void) key;
	return 0;
}

// Converts the list to a char**, returns NULL on failure
char **convert_env_to_array(t_list *env)
{
	printf("[INFO] convert_env_to_array not implemented yet");
	char **converted_env = NULL;

	(void) env;
	return converted_env;
}

// Converts the char** to a list, returns NULL on failure
t_list *convert_env_to_list(char **env)
{
	printf("[INFO] convert_env_to_array not implemented yet");
	t_list *converted_env = NULL;

	(void) env;
	return converted_env;
}
