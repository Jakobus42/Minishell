#include "core/parser/parser.h"

static const char *expected_tokens_to_string(t_token_type prv_token_type)
{
	if (prv_token_type == NONE || prv_token_type == PIPE)
		return "[WORD] or [REDIRECTION]";
	else if (prv_token_type == WORD)
		return "[WORD], [REDIRECTION] or [PIPE]";
	else
		return "[WORD]";
}

bool log_syntax_error(const t_token *token, t_token_type prv_token_type)
{
	dprintf(2, "Unexpected token '%s' of type '%s'. Expected token of type: %s\n",
	        token->value, token_type_to_str(token->type), expected_tokens_to_string(prv_token_type));
	return true;
}

bool is_expected_token(t_token_type prv_token_type, t_token_type token_type)
{
	if (prv_token_type == NONE || prv_token_type == PIPE)
		return token_type == WORD || is_redirect(token_type);
	else if (prv_token_type == WORD)
		return token_type == WORD || is_redirect(token_type) || token_type == PIPE;
	else
		return token_type == WORD;
}