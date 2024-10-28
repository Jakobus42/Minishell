#include "core/builtins/builtins.h"

static bool	sorted(char **arr)
{
	int	x;

	x = 0;
	while (arr && arr[x] && arr[x + 1])
	{
		if (ft_strcmp2(arr[x], arr[x + 1]) <= 0)
			x++;
		else
			return (false);
	}
	return (true);
}

static void	swap(char **arr, int x)
{
	char	*temp;

	if (!arr || !arr[x] || !arr[x + 1])
		return ;
	temp = arr[x];
	arr[x] = arr[x + 1];
	arr[x + 1] = temp;
}

void	sort_arr(char **arr)
{
	int		x;

	while (arr && !sorted(arr))
	{
		x = 0;
		while (arr && arr[x] && arr[x + 1])
		{
			if (ft_strcmp2(arr[x], arr[x + 1]) > 0)
				swap(arr, x);
			x++;
		}
	}
}
