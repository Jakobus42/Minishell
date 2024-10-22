#include "../../../include/core/env/env.h"

void reset_env_node(t_env *env)
{
	free_and_null(env->key);
	free_and_null(env->value);
}