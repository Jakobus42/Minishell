#ifndef ENV_H
#define ENV_H

void construct_env(char **env, t_list *menv);

typedef struct s_pair
{
	char *key;
	char *value;
} t_pair;

typedef struct s_env
{
	t_list *data;
} t_env;

void reset_env(t_env *env);

#endif // ENV_H