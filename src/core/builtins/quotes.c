/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 20:26:31 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/10/30 20:31:33 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/shell/shell.h"

bool	s_out_q(char *s)
{
	if (s && s[0] == '\'' && s[ft_strlen(s) - 1] == '\'')
		return (true);
	return (false);
}

bool	d_out_q(char *s)
{
	if (s && s[0] == '\"' && s[ft_strlen(s) - 1] == '\"')
		return (true);
	return (false);
}

bool	even_q(char *s)
{
	int	dq;
	int	sq;
	int	i;

	dq = 0;
	sq = 0;
	i = 0;
	if (!s)
		return (false);
	while (s[i])
	{
		if (s[i] == '\'')
			sq++;
		else if (s[i] == '\"')
			dq++;
		i++;
	}
	if (sq % 2 == 0 && dq % 2 == 0)
		return (true);
	return (false);
}

char	*rm_q(char *s)
{
	int		i;
	int		j;
	char	*new;

	i = -1;
	j = 0;
	if (!s)
		return (NULL);
	while (s[++i])
	{
		if (s[i] == '\'' || s[i] == '\"')
			j++;
	}
	new = ft_calloc(ft_strlen(s) - j + 1, sizeof(char));
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != '\'' && s[i] != '\"')
			new[j++] = s[i++];
		else
			i++;
	}
	return (new);
}

bool	only_digits(char *s, int start)
{
	if (!s || !s[start])
		return (false);
	while (s[start])
	{
		if (s[start] >= '0' && s[start] <= '9')
			start++;
		else
			return (false);
	}
	return (true);
}
