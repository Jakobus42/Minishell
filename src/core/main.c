#include "../../include/core/shell.h"

int main(int ac, char **av, char **env)
{
	t_shell shell;
	t_list  menv;

	if (ac < 0 || !av)
		return (1);
	ft_bzero(&menv, sizeof(t_list *));
	initialize_shell(&shell);
	reset_shell(&shell);
	if (VERBOSE)
	{
		debug_print_shell(&shell);
	}
	construct_env(env, &menv);
	execute_pipeline(&shell, env);
}
