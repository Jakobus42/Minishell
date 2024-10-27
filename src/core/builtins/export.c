#include "core/shell.h"
#include "core/builtins/builtins.h"

bool check_valid_export(char *s)
{
	size_t i;

	i = 0;
	if (s && (ft_isalpha(s[i]) || s[i] == '_'))
		return (false);
	else
		return (ft_putstr_fd(s, 2), ft_putendl_fd(": not a valid identifier\n", 2), true);
}

char	*checking_vars(char *s)
{
	char	*check;

	check = NULL;
	if (s_out_q(s) || d_out_q(s) || (even_q(s) && !s_out_q(s)))
		check = rm_q(s);
	if (check && !check_valid_export(check))
		return (check);
	else
		check = ft_strdup(s);
	return (check);
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
		if (pair->value)
		{
			ft_putstr_fd(pair->key, 1);
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(pair->value, 1);
			ft_putendl_fd("\"", 1);
		}
		else
			ft_putendl_fd(pair->key, 1);
		env_temp = env_temp->next;
	}
}

void set_export(t_shell *shell, t_command *cmd)
{
	char	**split;
	char	**check;
	int    i;

	i = 1;
	while (cmd->args[i])
	{
		split = ft_split(cmd->args[i], '=');
		if (!split)
			return (perror("ft_split failed"));
		check = ft_calloc(3, sizeof(char *));
		if (!check)
			return (free_array((void ***)&split), perror("calloc failed"));
		check[0] = checking_vars(split[0]);
		if (!check[0])
			return (free_array((void ***)&split), free_array((void ***)&check), perror("checking vars failed"));
		check[1] = ft_strdup(split[1]);
		if (!check[0])
			return (free_array((void ***)&split), free_array((void ***)&check), perror("ft_strdup failed"));
		free_array((void ***)&split);
		if (check[0] && check[1])
		{
			if (set_env(shell->env, check[0], check[1]))
				return (free_array((void ***)&check), perror("set_env failed"));
			free_array((void ***)&check);
		}
		i++;
	}
}
