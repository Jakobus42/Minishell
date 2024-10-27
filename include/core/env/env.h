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
bool    set_env(t_list *env, char *key, char *value);
bool    remove_env_pair(t_list *env, const char *key);
char  **convert_env_to_array(t_list *env);
t_list *convert_env_to_list(const char **env);
int     get_valid_key_size(const char *key);

/*ENV_UTILS*/
bool    lst_del_node(t_list *list, t_pair *pair);
void    free_pair(t_pair *pair);
t_pair *create_pair(const char *str, t_pair *pair);
bool    valid_env(t_shell *shell, char *s);
void    print_env(t_list *env);

#endif // ENV_H