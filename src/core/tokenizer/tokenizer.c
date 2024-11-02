/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 14:51:31 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/11/02 14:51:32 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/tokenizer/tokenizer.h"

static t_token_type	get_token_type(const char *input)
{
	if (*input == '>' && *(input + 1) == '>')
		return (REDIRECT_APPEND);
	else if (*input == '<' && *(input + 1) == '<')
		return (HEREDOC);
	else if (*input == '|')
		return (PIPE);
	else if (*input == '>')
		return (REDIRECT_OUT);
	else if (*input == '<')
		return (REDIRECT_IN);
	else
		return (WORD);
}

static size_t	get_word_size(const char *input)
{
	const char	*start = input;
	char		*quote;

	while (*input)
	{
		quote = ft_strchr(QUOTES, *input);
		if (quote)
			input = skip_quotes(input, *quote);
		else if (ft_strchr(METACHARACTERS, *input))
			break ;
		else
			input++;
	}
	return (input - start);
}

static size_t	get_token_size(const char *input, const t_token_type type)
{
	if (type == PIPE || type == REDIRECT_OUT || type == REDIRECT_IN)
		return (1);
	else if (type == REDIRECT_APPEND || type == HEREDOC)
		return (2);
	else
		return (get_word_size(input));
}

t_token	*next_token(const char **input)
{
	t_token				*token;
	t_token_type		type;
	size_t				size;

	skip_whitespaces(input);
	if (!**input)
		return (NULL);
	type = get_token_type(*input);
	size = get_token_size(*input, type);
	token = ft_calloc(sizeof(t_token), 1);
	if (!token)
		return (NULL);
	token->type = type;
	token->value = ft_substr(*input, 0, size);
	if (!token->value)
	{
		free(token);
		return (NULL);
	}
	*input += size;
	return (token);
}
