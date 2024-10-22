#ifndef SHELL_H
#define SHELL_H

#include "../../libft/libft.h"
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

typedef struct s_shell
{
	t_list     env;
	t_list     tokens;
	t_pipeline pipeline;
	uint8_t    error_code;
} t_shell;

#include "../utils/utils.h" // .-.

#endif // SHELL_H