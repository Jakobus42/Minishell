#include "core/shell.h"

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

