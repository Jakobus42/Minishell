#include "core/expander/expander.h"
#include "core/shell/shell.h"

void expand_tokens(t_shell *shell, t_list *tokens)
{
	t_token_type prv_token_type = NONE;
	while (tokens)
	{
		t_token *token = tokens->content;
		if (token->type == WORD && prv_token_type != HEREDOC)
		{
			char *expanded = expand_token(shell, token->value);
			log_message(LOG_DEBUG, "expanded: %s\n", expanded);
			free(expanded);
		}
		prv_token_type = token->type;
		tokens = tokens->next;
	}
}
