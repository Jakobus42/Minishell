#ifndef EXPANDER_H
#define EXPANDER_H

#include "core/expander/expander.h"
#include "libft/libft.h"

typedef struct s_shell t_shell;

void expand_tokens(t_shell *shell, t_list **tokens);

char *expand_token(t_shell *shell, const char *token);

char* read_into_heredoc(t_shell* shell, char* eof);

#endif // EXPANDER_H