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

typedef struct s_tokens
{
	t_list *data;
} t_tokens;

void     generate_tokens(t_shell *shell, const char *input);
t_token *next_token(const char **input);
void     reset_tokens(t_tokens *token);

#endif // TOKENIZER_H