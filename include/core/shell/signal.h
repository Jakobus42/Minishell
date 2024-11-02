#ifndef SIGNAL_H
# define SIGNAL_H

# include <core/shell/shell.h>
# include <signal.h>
# include <stdint.h>

# define CTRL_C 130
# define CTRL_BACKLASH 131

extern uint8_t	g_signal;

typedef enum e_mode
{
	MODE_NON_INTERACTIVE,
	MODE_INTERACTIVE,
	MODE_CHILD,
	MODE_HEREDOC
}				t_mode;

void			handle_signal(t_shell *shell, t_mode mode);

#endif // SIGNAL_H