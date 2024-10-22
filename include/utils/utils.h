#ifndef UTILS_H
#define UTILS_H

#include "../../include/core/shell.h"

// -- memory --
void free_and_null(void **ptr);
void free_array(void ***arr);

// -- debug --
void debug_print_env(t_list *env);
void debug_print_tokens(t_list *tokens);
void debug_print_pipeline(t_pipeline *pipeline);
void debug_print_shell(t_shell *shell);

#endif // UTILS_H