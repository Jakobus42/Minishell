#include "core/tokenizer/tokenizer.h"

const char *token_type_to_str(const t_token_type type)
{
	switch (type)
	{
	case WORD:
		return "[WORD]";
	case PIPE:
		return "[PIPE]";
	case REDIRECT_OUT:
		return "[REDIRECT_OUT]";
	case REDIRECT_APPEND:
		return "[REDIRECT_APPEND]";
	case REDIRECT_IN:
		return "[REDIRECT_IN]";
	case HEREDOC:
		return "[HEREDOC]";
	default:
		return "[NONE]";
	}
}

bool is_redirect(const t_token_type type)
{
	return type == REDIRECT_APPEND || type == REDIRECT_OUT || type == REDIRECT_IN || type == HEREDOC;
}