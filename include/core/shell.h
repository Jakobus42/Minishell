#ifndef SHELL_H
#define SHELL_H

#include "builtins/builtins.h"
#include "env/env.h"
#include "executor/executor.h"
#include "parser/parser.h"
#include "tokenizer/tokenizer.h"
#include <stdint.h>

typedef struct s_shell
{
	t_env      env;
	t_pipeline pipeline;
	uint8_t    error_code;
	t_exec     exec;
} t_shell;

#endif // SHELL_H