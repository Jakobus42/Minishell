#include "core/shell/shell.h"
#include "core/shell/signal.h"
#include <sys/ioctl.h>

void	handle_sigint_interactive(int sig)
{
	g_signal = sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	handle_sigint_heredoc(int sig)
{
	g_signal = sig;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_replace_line("", 0);
	rl_on_new_line();
}

void	handle_signal(t_shell *shell, t_mode mode)
{
	if (g_signal)
	{
		shell->error_code = g_signal + 128;
		g_signal = 0;
	}
	if (mode == MODE_CHILD)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	else if (mode == MODE_INTERACTIVE)
	{
		signal(SIGINT, &handle_sigint_interactive);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == MODE_NON_INTERACTIVE)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == MODE_HEREDOC)
	{
		signal(SIGINT, &handle_sigint_heredoc);
		signal(SIGQUIT, SIG_IGN);
	}
}
