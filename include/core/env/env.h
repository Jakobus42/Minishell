#ifndef ENV_H
#define ENV_H

#include "libft/libft.h"
#include "utils/utils.h"

typedef struct s_pair
{
	char *key;
	char *value;
} t_pair;

char   *get_env(t_list *env, const char *key);
bool    set_env(t_list *env, const char *key, const char *value);
bool    remove_env_pair(t_list *env, const char *key);
char  **convert_env_to_array(t_list *env);
t_list *convert_env_to_list(const char **env);

#endif // ENV_H