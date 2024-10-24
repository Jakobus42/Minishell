#include "core/parser/parser.h"

static const char *expected_tokens_to_string(t_parser_state state)
{
	switch (state)
	{
	case STATE_START:
		return "[WORD] [REDIRECT]";
	case STATE_WORD:
		return "[WORD], [REDIRECT] or [PIPE]";
	case STATE_PIPE:
		return "[WORD] or [REDIRECT]";
	case STATE_REDIRECT:
		return "[WORD]";
	case STATE_END:
		return "[WORD]";
	default:
		return "[UNKNOWN]";
	}
}

static const char *state_to_string(t_parser_state state)
{
	switch (state)
	{
	case STATE_START:
		return "[STATE_START]";
	case STATE_WORD:
		return "[STATE_WORD]";
	case STATE_PIPE:
		return "[STATE_PIPE]";
	case STATE_REDIRECT:
		return "[STATE_REDIRECT]";
	case STATE_END:
		return "[STATE_END]";
	default:
		return "[UNKNOWN]";
	}
}

bool log_syntax_error(const t_token *token, t_parser_state state)
{
	dprintf(2, "Unexpected token '%s' of type '%s' in state '%s'. Expected token of type: %s\n",
	        token->value, token_type_to_str(token->type), state_to_string(state), expected_tokens_to_string(state));
	return true;
}

bool is_expected_token(t_parser_state state, t_token_type token_type)
{
	switch (state)
	{
	case STATE_START:
		return token_type == WORD || is_redirect(token_type);
	case STATE_WORD:
		return token_type == WORD || is_redirect(token_type) || token_type == PIPE;
	case STATE_PIPE:
		return token_type == WORD || is_redirect(token_type);
	case STATE_REDIRECT:
		return token_type == WORD;
	case STATE_END:
		return token_type == WORD;
	default:
		return token_type == WORD;
	}
}