#include "../../include/core/shell.h"
#include <stdio.h>

int main(int ac, char **av, char **env)
{
	t_shell shell;

	if (ac < 0 || !av)
		return (1);
	initialize_shell(&shell);
	reset_shell(&shell);
	if (VERBOSE)
	{
		debug_print_shell(&shell);
	}
	execute_pipeline(&shell, env);
}