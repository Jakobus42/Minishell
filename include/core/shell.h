#ifndef SHELL_H
#define SHELL_H

#include "../../libraries/libft/libft.h"
#include "env/env.h"
#include "executor/executor.h"
#include "parser/parser.h"
#include "utils/utils.h"
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/wait.h>

#define VERBOSE false

#define GREEN "\033[38;2;152;251;152m"
#define YELLOW "\033[38;2;255;255;192m"
#define RESET "\033[0m"

#define PROMPT GREEN "shell<3 " RESET

typedef enum e_error_code
{
	SUCCESS = 0,
	ERROR = 1,

	ERROR_EXEC = 126,
	ERROR_CMD_NOT_FOUND = 127
} t_error_code;

// -- ERRORS --
#define MALLOC_FAIL "MALLOC Failed"

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
void reset_shell(t_shell *shell);
void error_exit(t_shell *shell, const char *error_msg, uint8_t error_code);

#endif // SHELL_H