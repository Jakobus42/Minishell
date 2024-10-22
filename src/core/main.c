#include "../../include/core/shell.h"
#include <stdio.h>

int main(void)
{
	t_shell shell;

	initialize_shell(&shell);
	reset_shell(&shell);
	if (VERBOSE)
	{
		debug_print_shell(&shell);
	}
}