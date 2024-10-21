#ifndef SHELL_H
#define SHELL_H

#include "builtins/builtins.h"
#include "env/env.h"
#include "executor/executor.h"
#include "parser/parser.h"
#include "tokenizer/tokenizer.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdint.h>

typedef struct s_shell
{
	t_env      env;
	t_pipeline pipeline;
	uint8_t    error_code;
} t_shell;

#endif // SHELL_H