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
void ft_free_double(char **smth);

// -- debug --
void        debug_print_env(t_env *env);
void        debug_print_pipeline(t_pipeline *pipeline);
void        debug_print_redirections(t_command *command);
const char *token_type_to_str(t_token_type type);

// -- string --
void  skip_whitespaces(const char **str);
char *ft_strjoin_null(char const *s1, char const *s2);

#endif // UTILS_H