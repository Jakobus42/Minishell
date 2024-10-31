#ifndef SIGNAL_H
#define SIGNAL_H

#include <stdint.h>
#include <core/shell/shell.h>
#include <signal.h>

extern uint8_t g_signal;

typedef enum e_mode {
    MODE_NON_INTERACTIVE,
    MODE_INTERACTIVE,
    MODE_CHILD,
    MODE_HEREDOC
} t_mode;

void handle_signal(t_shell* shell, t_mode mode);


#endif //SIGNAL_H