#ifndef UTILS_H
#define UTILS_H

#include "../../libft/libft.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct s_env      t_env;
typedef struct s_tokens   t_tokens;
typedef struct s_pipeline t_pipeline;
typedef struct s_shell    t_shell;

// -- memory --
void free_and_null(void **ptr);
void free_array(void ***arr);

// -- debug --
void debug_print_env(t_env *env);
void debug_print_tokens(t_tokens *tokens);
void debug_print_pipeline(t_pipeline *pipeline);
void debug_print_shell(t_shell *shell);

// -- string --
void skip_whitespaces(const char **str);

#endif // UTILS_H