#include "core/builtins/builtins.h"
#include "core/parser/parser.h"
#include "core/shell/shell.h"

void	reset_fds(int copy_stdin, int copy_stdout)
{
	if (copy_stdin != -1)
	{
		if (dup2(copy_stdin, STDIN_FILENO) == -1)
			return (close(copy_stdin), perror("dup2 reset stdin failed"));
		close(copy_stdin);
	}
	if (copy_stdout != -1)
	{
		if (dup2(copy_stdout, STDOUT_FILENO) == -1)
			return (close(copy_stdout), perror("dup2 reset stdout failed"));
		close(copy_stdout);
	}
}

void	redirect_builtin(t_shell *shell)
{
	if (shell->exec.infile)
	{
		if (dup2(shell->exec.infile, STDIN_FILENO) == -1)
			return (close(shell->exec.infile), perror("dup2 failed"));
		close(shell->exec.infile);
	}
	if (shell->exec.outfile)
	{
		if (dup2(shell->exec.outfile, STDOUT_FILENO) == -1)
			return (close(shell->exec.infile), perror("dup2 failed"));
		close(shell->exec.outfile);
	}
}
