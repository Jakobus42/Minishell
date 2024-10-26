#ifndef ERROR_H
#define ERROR_H

typedef struct s_shell t_shell;

typedef enum e_exit_code
{
	SUCCESS = 0,
	ERROR = 1,
	FATAL = 2
} t_error_code;

void reset_shell(t_shell *shell);
void error_fatal(t_shell *shell);

#endif //ERROR_H