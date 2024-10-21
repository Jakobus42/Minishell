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
	char     **env;
	uint8_t    error_code;
	t_pipeline pipeline;
} t_shell;

#endif // SHELL_H