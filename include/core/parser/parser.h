#ifndef PARSER_H
#define PARSER_H

#include "core/tokenizer/tokenizer.h"
#include "libft/libft.h"

typedef struct s_redirection
{
	t_token_type type;
	char        *file_name;
} t_redirection;

typedef struct s_command
{
	t_list *redir; // TODO rename to redirs
	char  **args;
	int     argc;
} t_command;

typedef struct s_pipeline
{
	t_list *commands;
	int     num_commands;
} t_pipeline;

bool parse_tokens(const t_list *tokens, t_pipeline *pipeline);
bool process_token(t_command *command, const t_token *token, t_token_type prv_token_type);
bool log_syntax_error(const t_list *tokens, t_token_type prv_token_type);
bool is_expected_token(t_token_type prv_token_type, const t_list *tokens);

#endif // PARSER_H