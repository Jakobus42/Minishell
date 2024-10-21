#ifndef TOKENIZER_H
#define TOKENIZER_H

#define METACHARACTERS "|<>" //&;()
#define QUOTES "\"'"

typedef enum e_token_type
{
	WORD,
	OPERATOR
} t_token_type;

typedef struct s_tokens
{
	t_token_type type;
	char        *token;
	t_tokens    *next;
} t_tokens;

#endif // TOKENIZER_H