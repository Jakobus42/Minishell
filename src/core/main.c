#include "../../include/core/shell.h"
#include <stdio.h>

int main(void)
{
	t_shell shell;

	initialize_shell(&shell);
	while (true)
	{
		const char *input = readline(PROMPT);
		if (!input)
			error_exit(&shell, "", ERROR_GENERAL);
		generate_tokens(&shell, input);
		if (VERBOSE)
			debug_print_shell(&shell);
		reset_shell(&shell);
	}
}