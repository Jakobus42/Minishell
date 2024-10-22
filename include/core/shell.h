#ifndef SHELL_H
#define SHELL_H

#include "../utils/utils.h"
#include "builtins/builtins.h"
#include "env/env.h"
#include "executor/executor.h"
#include "parser/parser.h"
#include "tokenizer/tokenizer.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdint.h>
#include <stdio.h>

#define VERBOSE true

// -- ERRORS --
#define MALLOC_FAIL "MALLOC Failed"

typedef struct s_shell
{
	t_env      env;
	t_tokens   tokens;
	t_pipeline pipeline;
	uint8_t    error_code;
	t_exec     exec;
} t_shell;

void initialize_shell(t_shell *shell);
void reset_shell(t_shell *shell);

#endif // SHELL_H