/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 14:51:51 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/11/02 14:51:52 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/tokenizer/tokenizer.h"
#include "utils/utils.h"

bool	update_quote_state(char *quote_state, const char current_char)
{
	if (ft_strchr(QUOTES, current_char))
	{
		if (!*quote_state)
		{
			*quote_state = current_char;
			return (true);
		}
		else if (current_char == *quote_state)
		{
			*quote_state = 0;
			return (true);
		}
	}
	return (false);
}

char	*remove_quotes(char *eof)
{
	char	*result;
	char	quote_state;
	int		i;

	result = eof;
	quote_state = 0;
	i = 0;
	while (*eof)
	{
		if (update_quote_state(&quote_state, *eof))
			eof++;
		else
		{
			result[i] = *eof;
			eof++;
			i++;
		}
	}
	result[i] = '\0';
	return (result);
}

const char	*skip_quotes(const char *input, const char quote)
{
	if (quote)
	{
		input++;
		while (*input && *input != quote)
			input++;
		if (*input == quote)
			input++;
	}
	return (input);
}
