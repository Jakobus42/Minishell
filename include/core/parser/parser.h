#ifndef PARSER_H
#define PARSER_H

#include "../../../include/core/tokenizer/tokenizer.h"
#include "../../../include/utils/utils.h"
#include "../../../libft/libft.h"

typedef struct s_redirection
{
	t_token_type type;
	char        *file_name;
} t_redirection;

typedef struct s_command
{
	t_list *redir;
	char   *cmd;
	char  **args;
} t_command;

typedef struct s_pipeline
{
	t_list *commands;
	int     num_commands;
} t_pipeline;

void reset_pipeline(t_pipeline *pipeline);

#endif // PARSER_H