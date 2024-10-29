#include "core/expander/expander.h"
#include "core/shell/shell.h"

void replace_token(t_list **tokens, t_list **cur, char *expanded_token)
{
	t_token *token = (t_token *) (*cur)->content;
	if (!ft_strlen(expanded_token) && !ft_strchr(token->value, '\'') &&
	    !ft_strchr(token->value, '"'))
	{
		log_message(LOG_WARNING, "expanded target token `%s` to NONE.\n", token->value);
		log_message(LOG_WARNING, "removing token: `%s` with type: %s from token list\n",
		            token->value, token_type_to_str(token->type));
		*cur = ft_lsterase_node(tokens, *cur, &free_token);
		free(expanded_token);
	}
	else
	{
		log_message(LOG_INFO, "expanded target token `%s` to `%s`\n", token->value, expanded_token);
		free(token->value);
		token->value = expanded_token;
	}
}

void expand_tokens(t_shell *shell, t_list **tokens)
{
	t_token_type prv_token_type = NONE;
	t_list      *cur = *tokens;

	while (cur)
	{
		t_token *token = cur->content;
		if (token->type == WORD && prv_token_type != HEREDOC)
		{
			char *expanded_token = expand_token(shell, token->value);
			replace_token(tokens, &cur, expanded_token);
			if (!cur)
				break;
			token = cur->content;
		}
		prv_token_type = token->type;
		cur = cur->next;
	}
}
