#ifndef SHELL_H
#define SHELL_H

#include "core/error.h"
#include "core/env/env.h"
#include "utils/utils.h"
#include "libft/libft.h"
#include "utils/logger.h"
#include "core/parser/parser.h"
#include "core/executor/executor.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>
#include <errno.h>

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
	uint8_t    error_code;
} t_shell;

void initialize_shell(t_shell *shell, const char **env);
bool setup_pipeline(t_shell *shell, const char *input);

#endif // SHELL_H