#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "utils/utils.h"

# define METACHARACTERS " \t\n|<>" // '&', ';', '(', ')'
# define QUOTES "\"'"

typedef enum e_token_type
{
	NONE,
	WORD,
	PIPE,
	REDIRECT_OUT,
	REDIRECT_APPEND,
	REDIRECT_IN,
	HEREDOC
}					t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
}					t_token;

// -- tokenizer.c --
t_token				*next_token(const char **input);

// -- token_types.c
const char			*token_type_to_str(const t_token_type type);
bool				is_redirect(const t_token_type type);

#endif // TOKENIZER_H