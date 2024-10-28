#ifndef UTILS_H
#define UTILS_H

#include "libft/libft.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct s_env      t_env;
typedef struct s_tokens   t_tokens;
typedef struct s_pipeline t_pipeline;
typedef struct s_shell    t_shell;
typedef struct s_command  t_command;
typedef enum e_token_type t_token_type;

// -- memory --
void free_and_null(void **ptr);
void free_array(void ***arr);

// -- debug --
void        debug_print_env(t_list *env);
void        debug_print_pipeline(t_pipeline *pipeline);
void        debug_print_redirections(t_list *redir);
const char *token_type_to_str(t_token_type type);

// -- string --
void        skip_whitespaces(const char **str);
const char *skip_quotes(const char *input, const char quote);
char       *ft_strjoin_null(char const *s1, char const *s2);

// -- quote --
bool update_quote_state(char *quote_state, const char current_char);

#endif // UTILS_H