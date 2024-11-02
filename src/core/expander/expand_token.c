/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 14:50:46 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/11/02 15:19:54 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/expander/expander.h"
#include "core/shell/shell.h"

static char	*fetch_expand_value(t_shell *shell, const char **token)
{
	t_pair	pair;
	int		key_size;

	key_size = vks(*token);
	pair.key = ft_substr(*token, 0, key_size);
	if (!pair.key)
		error_fatal(shell, "ft_substr in fetch_expanded_value\n", MALLOC_FAIL);
	*token += key_size;
	pair.value = get_env(shell, shell->env, pair.key);
	free(pair.key);
	return (pair.value);
}

static int	expand_variable(t_shell *shell, const char **token, char *output)
{
	char	*value;
	int		size;

	while (*token && **token == '$')
		(*token)++;
	if (**token == '?')
	{
		value = ft_itoa(shell->error_code);
		if (!value)
			error_fatal(shell, "ft_itoa in fetch_expanded_value\n",
				MALLOC_FAIL);
		(*token)++;
	}
	else
		value = fetch_expand_value(shell, token);
	if (!value)
		return (0);
	size = ft_strlen(value);
	if (output)
		ft_strlcpy(output, value, size + 1);
	free(value);
	return (size);
}

static void	handle_quotes(char *out, const bool rm_q, int *s, const char **tok)
{
	if (out && !rm_q)
		out[*s] = **tok;
	if (!rm_q)
		(*s)++;
	(*tok)++;
}

static int	process_exp(t_shell *s, const char *t, char *out, const bool rm_q)
{
	int		size;
	char	q;

	size = 0;
	q = 0;
	while (*t)
	{
		if (update_quote_state(&q, *t))
			handle_quotes(out, rm_q, &size, &t);
		else if (q != '\'' && *t == '$' && (vks(t + 1) > 0 || *(t + 1) == '?'))
		{
			if (out)
				size += expand_variable(s, &t, &out[size]);
			else
				size += expand_variable(s, &t, NULL);
		}
		else
		{
			if (out)
				out[size] = *t;
			size++;
			t++;
		}
	}
	return (size);
}

char	*expand_token(t_shell *shell, const char *token,
		const bool remove_quotes)
{
	const int	expected_size = process_exp(shell, token, NULL, remove_quotes);
	char		*expanded_token;

	expanded_token = ft_calloc(sizeof(char), expected_size + 1);
	if (!expanded_token)
		error_fatal(shell, "ft_calloc in expand_token", MALLOC_FAIL);
	process_exp(shell, token, expanded_token, remove_quotes);
	return (expanded_token);
}
