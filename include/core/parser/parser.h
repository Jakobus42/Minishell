#ifndef PARSER_H
#define PARSER_H

#include "core/error.h"
#include "core/tokenizer/tokenizer.h"
#include "libft/libft.h"
#include "utils/logger.h"

typedef struct s_redirection
{
	t_token_type type;
	char        *file_name;
} t_redirection;

typedef struct s_command
{
	t_list *redirs;
	char  **args;
	int     argc;
} t_command;

typedef struct s_pipeline
{
	t_list *commands;
	int     num_commands;
} t_pipeline;

// -- parser.c --
bool parse_tokens(t_shell *shell, const t_list *tokens);

// -- process_token.c --
void process_token(t_shell *shell, t_command *command, const t_token *token);

// -- syntax.c --
bool validate_token_sequence(const t_list *tokens);

#endif // PARSER_H