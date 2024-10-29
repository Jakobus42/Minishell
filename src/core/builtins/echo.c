#include "core/builtins/builtins.h"

static bool is_n_option(const char *token)
{
	if (!token || token[0] != '-')
	{
		return false;
	}
	token++;
	while (*token)
	{
		if (*token != 'n')
		{
			return false;
		}
		token++;
	}
	return true;
}

int echo(char **tokens)
{
	int  x = 1;
	bool n_option = false;

	while (tokens[x] && is_n_option(tokens[x]))
	{
		n_option = true;
		x++;
	}
	while (tokens[x])
	{
		ft_putstr_fd(tokens[x], 1);
		x++;
		if (tokens[x])
			ft_putstr_fd(" ", 1);
	}
	if (!n_option)
		ft_putstr_fd("\n", 1);
	return 0;
}
