#include "../../../include/core/tokenizer/tokenizer.h"

void reset_tokens(t_tokens *tokens)
{
	while (tokens->data)
	{
		t_token *token = (t_token *) tokens->data->content;
		free_and_null((void **) &token->value);
		tokens->data = tokens->data->next;
	}
}