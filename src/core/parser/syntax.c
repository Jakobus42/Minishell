#include "core/parser/parser.h"

const char *expected_tokens_to_string(t_token_type prv_token_type, const t_list *tokens)
{
	if (!tokens->next || prv_token_type == NONE)
		return "[WORD] or [EOF]";
	else if (prv_token_type == PIPE)
		return "[WORD], [REDIRECT_OUT], [REDIRECT_APPEND], [REDIRECT_IN] or "
		       "[HEREDOC]";
	else if (prv_token_type == WORD)
		return "[WORD], [REDIRECT_OUT], [REDIRECT_APPEND], [REDIRECT_IN], "
		       "[HEREDOC] or [PIPE]";
	else
		return "[WORD]";
}

bool log_syntax_error(const t_list *tokens, t_token_type prv_token_type)
{
	t_token *token = (t_token *) tokens->content;
	dprintf(2, "minishell: unexpected token '%s' of type '%s' expected token of type: %s\n",
	        token->value, token_type_to_str(token->type), expected_tokens_to_string(prv_token_type, tokens));
	return true;
}

bool is_expected_token(t_token_type prv_token_type, const t_list *tokens)
{
	t_token *token = (t_token *) tokens->content;

	if (!tokens->next || prv_token_type == NONE)
		return token->type == WORD;
	else if (prv_token_type == PIPE)
		return token->type == WORD || is_redirect(token->type);
	else if (prv_token_type == WORD)
		return token->type == WORD || is_redirect(token->type) || token->type == PIPE;
	else
		return token->type == WORD;
}