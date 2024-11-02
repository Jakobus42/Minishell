/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 14:50:09 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/11/02 14:50:10 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	int	x;

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

bool	check_valid_export(char *s)
{
	size_t	i;

	i = 0;
	if (s && (ft_isalpha(s[i]) || s[i] == '_'))
	{
		i++;
		while (s[i] && (ft_isalnum(s[i]) || s[i] == '_'))
			i++;
		if (i == ft_strlen(s))
			return (true);
	}
	return (false);
}

int	find_char(char *s, int lim)
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
