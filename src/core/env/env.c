#include "../../../include/core/env/env.h"

void reset_env(t_env *env)
{
	while (env->data)
	{
		t_pair *content = (t_pair *) env->data->content;
		free_and_null((void **) &content->value);
		free_and_null((void **) &content->key);
		env->data = env->data->next;
	}
}