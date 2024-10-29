#include "core/builtins/builtins.h"

static bool check_n(char *token)
{
	int  x;
	bool n;

	n = true;
	x = 0;
	if (!token || ft_strlen(token) < 2)
		return (false);
	while (n && token[x])
	{
		if (x == 0 && token[x] == '-')
			x++;
		else if (x >= 1 && token[x] == 'n')
			x++;
		else if (x >= 2)
		{
			if (token[x] == 'n')
				x++;
			else if (token[x - 1] == 'n' && token[x] == ' ')
			{
				while (token[x] && token[x] == ' ')
					x++;
			}
			else
				n = false;
		}
		else
			n = false;
	}
	return (n);
}

int echo(char **token)
{
	int x;

	x = 0;
	if (!token[x] || ft_strcmp(token[x], "echo"))
		return (1);
	if (!token[x + 1])
		return (ft_putstr_fd("\n", 1), 0);
	x++;
	while (token[x])
	{
		if (x == 1 && check_n(token[x]))
			x++;
		else if (x > 1 && check_n(token[x - 1]) && check_n(token[x]))
			x++;
		else
		{
			ft_putstr_fd(token[x], 1);
			if (token[x] && token[x + 1])
				ft_putstr_fd(" ", 1);
			x++;
		}
	}
	if (check_n(token[1]))
		return (0);
	return (ft_putstr_fd("\n", 1), 0);
}
