#include "../../../include/core/tokenizer/tokenizer.h"

void reset_token(t_token *token)
{
	free_and_null((void **) &token);
}