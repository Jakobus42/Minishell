#ifndef TOKENIZER_H
#define TOKENIZER_H

#include "../../../include/utils/utils.h"

#define METACHARACTERS "|<>" //&;()
#define QUOTES "\"'"
#define WHITESPACES " \t\n\r\v\f"

typedef enum e_token_type
{
	WORD,
	DQ_WORD,
	SQ_WORD,
	PIPE,
	REDIRECT_OUT,
	REDIRECT_APPEND,
	REDIRECT_IN,
	HEREDOC
} t_token_type;

typedef struct s_token
{
	t_token_type type;
	char        *value;
} t_token;

t_token *next_token(const char **input);

#endif // TOKENIZER_H