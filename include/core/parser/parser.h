#ifndef PARSER_H
#define PARSER_H

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
	char	     **cmd;
	t_redirection *redir;
} t_command;

typedef struct s_pipeline
{
	t_command *commands;
	int        num_commands;
} t_pipeline;

#endif // PARSER_H