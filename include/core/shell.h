#ifndef SHELL_H
#define SHELL_H

#include "../utils/utils.h"
#include "builtins/builtins.h"
#include "env/env.h"
#include "executor/executor.h"
#include "parser/parser.h"
#include "tokenizer/tokenizer.h"
#include <errno.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdint.h>
#include <stdio.h>

#define VERBOSE true
#define PROMPT "> "

typedef enum e_error_code
{
	SUCCESS = 0,
	ERROR = 1,

	ERROR_EXEC = 126,
	ERROR_CMD_NOT_FOUND = 127
} t_error_code;

typedef struct s_shell
{
	t_env      env;
	t_pipeline pipeline;
	uint8_t    error_code;
} t_shell;

void initialize_shell(t_shell *shell);
bool setup_pipeline(t_shell *shell, const char *input);
void reset_shell(t_shell *shell);
void error_exit(t_shell *shell, const char *error_msg, uint8_t error_code);

#endif // SHELL_H