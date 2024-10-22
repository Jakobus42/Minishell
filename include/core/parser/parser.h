#ifndef PARSER_H
#define PARSER_H

#include "../../../include/utils/utils.h"
#include "../../../libft/libft.h"

typedef enum e_redir_type
{
	REDIR_NONE,
	REDIR_INPUT,
	REDIR_HEREDOC,
	REDIR_OUTPUT,
	REDIR_APPEND
} t_redir_type;

typedef struct s_redirection
{
	t_redir_type type;
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