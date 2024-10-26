#ifndef SHELL_H
#define SHELL_H

#include "../../libraries/libft/libft.h"
#include "env/env.h"
#include "executor/executor.h"
#include "parser/parser.h"
#include "utils/utils.h"
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/wait.h>

#define VERBOSE true

#define GREEN "\033[38;2;152;251;152m"
#define YELLOW "\033[38;2;255;255;192m"
#define RESET "\033[0m"

#define COLOR_DEBUG "\033[34m"
#define COLOR_INFO "\033[32m"
#define COLOR_WARNING "\033[33m"
#define COLOR_ERROR "\033[31m"
#define COLOR_CRITICAL "\033[41m"

#define PROMPT GREEN "shell<3 " RESET

typedef enum e_error_code
{
	SUCCESS = 0,
	ERROR = 1,

	ERROR_EXEC = 126,
	ERROR_CMD_NOT_FOUND = 127
} t_error_code;

typedef enum e_log_level
{
	LOG_DEBUG,
	LOG_INFO,
	LOG_WARNING,
	LOG_ERROR,
	LOG_CRITICAL
} t_log_level;

typedef struct s_shell
{
	t_list    *env;
	t_list    *tokens;
	t_pipeline pipeline;
	t_exec     exec;
	uint8_t    error_code;
} t_shell;

void initialize_shell(t_shell *shell, const char **env);
bool setup_pipeline(t_shell *shell, const char *input);
void reset_shell(t_shell *shell);
void error_exit(t_shell *shell, const char *error_msg, uint8_t error_code);
void log_message(t_log_level log_level, const char *format, ...);

#endif // SHELL_H