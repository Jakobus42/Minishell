#include "../../include/core/shell.h"
#include <stdio.h>

int main(void)
{
	t_shell shell;
	printf("Hello World!\n");
	if (VERBOSE)
	{
		debug_print_shell(&shell);
	}
}