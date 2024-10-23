#include "core/tokenizer/tokenizer.h"

bool is_word(const t_token_type type)
{
	return type == WORD || type == DQ_WORD || type == SQ_WORD;
}

bool is_redirect(const t_token_type type)
{
	return type == REDIRECT_APPEND || type == REDIRECT_OUT || type == REDIRECT_IN || type == HEREDOC;
}