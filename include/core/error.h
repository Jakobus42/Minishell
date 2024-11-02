#ifndef ERROR_H
# define ERROR_H

# include <stdint.h>

typedef struct s_shell	t_shell;

# define MALLOC_FAIL 1

void					reset_shell(t_shell *shell);
void					error_fatal(t_shell *shell, const char *msg,
							uint8_t error_code);

#endif // ERROR_H