#include "core/shell.h"

bool check_valid_export(const char *key, const char *value)
{
	size_t i;
	int    flag;

	i = 0;
	if (key && (ft_isalpha(key[i]) || key[i] == '_'))
	{
		i++;
		while (key && ft_isalnum(key[i]))
			i++;
	}
	if (i == ft_strlen(key))
		flag = 1;
	else
		return (perror(key), true);
	i = 0;
	if (value && (ft_isalpha(value[i]) || value[i] == '_'))
	{
		i++;
		while (value && ft_isalnum(value[i]))
			i++;
	}
	if (i == ft_strlen(value) && flag == 1)
		return (false);
	return (perror(value), true);
}

void print_env(t_list *env)
{
	t_list *env_temp;
	t_pair *pair;

	env_temp = env;
	while (env_temp)
	{
		pair = (t_pair *) env_temp->content;
		if (pair->value)
		{
			ft_putstr_fd(pair->key, 1);
			ft_putstr_fd("=", 1);
			ft_putendl_fd(pair->value, 1);
		}
		env_temp = env_temp->next;
	}
}

void print_export(t_list *env)
{
	t_list *env_temp;
	t_pair *pair;

	env_temp = env;
	while (env_temp)
	{
		pair = (t_pair *) env_temp->content;
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(pair->key, 1);
		ft_putstr_fd("=\"", 1);
		ft_putstr_fd(pair->value, 1);
		ft_putendl_fd("\"", 1);
		env_temp = env_temp->next;
	}
}