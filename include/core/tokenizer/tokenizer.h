#ifndef TOKENIZER_H
#define TOKENIZER_H

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

#endif // TOKENIZER_H