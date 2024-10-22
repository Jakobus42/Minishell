#ifndef TOKENIZER_H
#define TOKENIZER_H

#include "../../../include/utils/utils.h"

#define METACHARACTERS "|<>" //&;()
#define QUOTES "\"'"

typedef enum e_token_type
{
	WORD,
	OPERATOR
} t_token_type;

typedef struct s_token
{
	t_token_type type;
	char        *token;
} t_token;

typedef struct s_tokens
{
	t_list *data;
} t_tokens;

void reset_tokens(t_tokens *token);

#endif // TOKENIZER_H