#ifndef PARSER_H
#define PARSER_H

#include "core/tokenizer/tokenizer.h"
#include "libft/libft.h"

typedef enum e_parser_state
{
	STATE_START,
	STATE_WORD,
	STATE_REDIRECT,
	STATE_PIPE,
	STATE_END
} t_parser_state;

typedef struct s_redirection
{
	t_token_type type;
	char        *file_name;
} t_redirection;

typedef struct s_command
{
	t_list *redir; // TODO rename to redirs
	char   *cmd;
	char  **args;
} t_command;

typedef struct s_pipeline
{
	t_list *commands;
	int     num_commands;
} t_pipeline;

bool parse_tokens(const t_list *tokens, t_pipeline *pipeline);
bool process_token(t_command *command, const t_token *token, t_parser_state *state);

#endif // PARSER_H