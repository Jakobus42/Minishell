#ifndef ENV_H
#define ENV_H

#include "../../../include/utils/utils.h"

typedef struct s_env
{
	char *key;
	char *value;
} t_env;

void reset_env_node(t_env *env);

#endif // ENV_H