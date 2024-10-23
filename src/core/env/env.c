#include "../../../include/core/shell.h"

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