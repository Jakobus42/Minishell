#include "core/shell.h"
#include "core/builtins/builtins.h"

bool check_valid_export(char *s)
{
	size_t i;

	i = 0;
	if (s && (ft_isalpha(s[i]) || s[i] == '_'))
		return (true);
	else
		return (false);
}

char	*checking_vars(char *s)
{
	char	*check;

	check = NULL;
	if (s_out_q(s) || d_out_q(s) || (even_q(s) && !s_out_q(s)))
		check = rm_q(s);
	if (check && check_valid_export(check))
		return (check);
	else
		return (free_and_null((void **)&check), ft_strdup(""));
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
		if (ft_strlen(pair->value) > 0)
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

static int	find_char(char *s, int lim)
{
	int	i;

	i = -1;
	while (s && s[++i])
	{
		if (s[i] == lim)
			return (i);
	}
	return (i);
}

static char	**split_once(char *s, int lim)
{
	char	**new;
	char	*temp;
	int		lim_pos;

	lim_pos = 0;
	new = ft_calloc(3, sizeof(char *));
	if (!new)
		return (NULL);
	lim_pos = find_char(s, lim);
	if (lim_pos == -1)
		return (NULL);
	temp = ft_substr(s, 0, lim_pos);
	if (!temp)
		return (perror("substr failed"), NULL);
	new[0] = checking_vars(temp);
	if (!new[0])
		return (free_and_null((void **)&temp), NULL);
	new[1] = ft_substr(s, lim_pos + 1, (ft_strlen(s) - lim_pos + 1));
	if (!new[1])
		return (free_array((void ***)&new), perror("substr failed"), NULL);
	return (new);
}

void set_export(t_shell *shell, t_command *cmd)
{
	char	**split;
	int    i;

	i = 1;
	while (cmd->args[i])
	{
		split = split_once(cmd->args[i], '=');
		if (ft_strlen(split[0]) == 0)
		{
			free_array((void ***)&split);
			ft_putstr_fd("export: ", 2);
			ft_putstr_fd(cmd->args[i], 2);
			ft_putendl_fd(": not a valid identifier\n", 2);
		}
		else if (split[0] && split[1])
		{
			if (set_env(shell->env, split[0], split[1]))
				return (free_array((void ***)&split), perror("set_env failed"));
			free_array((void ***)&split);
		}
		i++;
	}
}
