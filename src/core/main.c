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
			error_exit(&shell, "readline", ERROR);
		if (!setup_pipeline(&shell, input))
		{
			if (VERBOSE)
				debug_print_pipeline(&shell.pipeline);
			// execute()
		}
		reset_shell(&shell);
	}
}