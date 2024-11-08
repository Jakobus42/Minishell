/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 14:50:49 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/11/02 14:50:50 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/expander/expander.h"
#include "core/shell/shell.h"

bool	replace_token(t_list **tokens, t_list **cur, char *expanded_token)
{
	t_token	*token;

	token = (t_token *)(*cur)->content;
	if (!ft_strlen(expanded_token) && !ft_strchr(token->value, '\'')
		&& !ft_strchr(token->value, '"'))
	{
		log_message(LOG_WARNING, "expanded target token `%s` to NONE.\n",
			token->value);
		log_message(LOG_WARNING, "removing token: `%s` with type:"
			"%s from token list\n", token->value,
			token_type_to_str(token->type));
		*cur = ft_lsterase_node(tokens, *cur, &free_token);
		free(expanded_token);
		return (true);
	}
	else
	{
		log_message(LOG_INFO, "expanded target token `%s` to `%s`\n",
			token->value, expanded_token);
		free(token->value);
		token->value = expanded_token;
		return (false);
	}
}

static void	advance_tokens(t_list **list, t_token_type *prv_tok, t_token *tok)
{
	*prv_tok = tok->type;
	*list = (*list)->next;
}

void	expand_tokens(t_shell *shell, t_list **tokens)
{
	t_token_type	prv_token_type;
	t_token			*token;
	char			*expanded_token;
	t_list			*cur;
	bool			was_removed;

	prv_token_type = NONE;
	cur = *tokens;
	while (cur)
	{
		token = cur->content;
		if (token->type == WORD && prv_token_type != HEREDOC)
		{
			expanded_token = expand_token(shell, token->value, true);
			was_removed = replace_token(tokens, &cur, expanded_token);
			if (!was_removed)
				advance_tokens(&cur, &prv_token_type, token);
			else
				prv_token_type = NONE;
		}
		else
			advance_tokens(&cur, &prv_token_type, token);
	}
}
