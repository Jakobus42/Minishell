#include "core/shell/shell.h"

uint8_t g_signal = 0;

int main(int argc, const char **argv, const char **env)
{
	t_shell shell;

	if(initialize_shell(&shell, argc, argv, env))
		return 1;
	run_shell(&shell);
}
