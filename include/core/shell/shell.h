#ifndef SHELL_H
#define SHELL_H

#include "core/env/env.h"
#include "core/error.h"
#include "core/executor/executor.h"
#include "core/parser/parser.h"
#include "libft/libft.h"
#include "utils/logger.h"
#include "utils/utils.h"
#include <errno.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <sys/wait.h>

#define GREEN "\033[38;2;152;251;152m"
#define YELLOW "\033[38;2;255;255;192m"
#define RESET "\033[0m"

#define PROMPT GREEN "shell<3 " RESET

typedef struct s_shell
{
	t_list    *env;
	t_list    *tokens;
	t_pipeline pipeline;
	t_exec     exec;
	char      *input;
	size_t	   shell_lvl;
	uint8_t    error_code;
} t_shell;

bool    initialize_shell(t_shell *shell, const int argc, const char** argv, const char** env);
void    run_shell(t_shell *shell);

void free_env(void *content);
void free_token(void *content);

#endif // SHELL_H