#include "core/parser/parser.h"

static const char *expected_tokens_to_string(t_token_type prv_type, bool is_last)
{
	if (is_last)
		return "[WORD] or [EOF]";
	else if (prv_type == NONE)
		return "[WORD], [REDIRECT_OUT], [REDIRECT_APPEND], [REDIRECT_IN] or "
		       "[HEREDOC]";
	else if (prv_type == PIPE)
		return "[WORD], [REDIRECT_OUT], [REDIRECT_APPEND], [REDIRECT_IN] or "
		       "[HEREDOC]";
	else if (prv_type == WORD)
		return "[WORD], [REDIRECT_OUT], [REDIRECT_APPEND], [REDIRECT_IN], "
		       "[HEREDOC] or [PIPE]";
	else
		return "[WORD]";
}

static bool is_expected_token(t_token_type prv_type, t_token_type curr_type, bool is_last)
{
	if (is_last)
		return curr_type == WORD;
	else if (prv_type == NONE)
		return curr_type == WORD || is_redirect(curr_type);
	else if (prv_type == PIPE)
		return curr_type == WORD || is_redirect(curr_type);
	else if (prv_type == WORD)
		return curr_type == WORD || is_redirect(curr_type) || curr_type == PIPE;
	else
		return curr_type == WORD;
}

static bool scan_for_unclosed_quotes(char *token)
{
	char quote_state = 0;
	if (!token)
		return 0;
	while (*token)
		update_quote_state(&quote_state, *token++);
	return quote_state != 0;
}

static void print_syntax_error(const t_list *tokens, const t_token *token, t_token_type prv_token_type)
{
	if (VERBOSE)
	{
		log_message(LOG_ERROR, "syntax error near unexpected token '%s' of type '%s' expected token of type: %s\n",
		            token->value, token_type_to_str(token->type), expected_tokens_to_string(prv_token_type, tokens->next == false));
	}
	else
	{
		log_message(LOG_ERROR, "syntax error near unexpected token `%s'\n",
		            token->value);
	}
}

bool validate_token_sequence(const t_list *tokens)
{
	t_token_type prv_token_type = NONE;

	while (tokens)
	{
		const t_token *token = tokens->content;
		if (scan_for_unclosed_quotes(token->value))
		{
			log_message(LOG_ERROR, "detected unclosed quote in token: `%s` of type: %s\n",
			            token->value, token_type_to_str((token->type)));
			return true;
		}
		if (!is_expected_token(prv_token_type, token->type, tokens->next == false))
		{
			print_syntax_error(tokens, token, prv_token_type);
			return true;
		}
		prv_token_type = token->type;
		tokens = tokens->next;
	}
	return false;
}
