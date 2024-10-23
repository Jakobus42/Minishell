#ifndef SHELL_H
#define SHELL_H

#include "core/env/env.h"
#include "core/executor/executor.h"
#include "core/parser/parser.h"
#include "utils/utils.h"
#include <errno.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdint.h>

#define VERBOSE true
#define PROMPT "> "

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
	uint8_t    error_code;
} t_shell;

void initialize_shell(t_shell *shell, const char **env);
bool setup_pipeline(t_shell *shell, const char *input);
void reset_shell(t_shell *shell);
void error_exit(t_shell *shell, const char *error_msg, uint8_t error_code);

#endif // SHELL_H