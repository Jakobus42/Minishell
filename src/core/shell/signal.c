#include "core/shell/signal.h"
#include "core/shell/shell.h"
#include <signal.h>

void handle_sigint_interactive(int sig) {
    g_signal = sig;
    write(1, "\n", 1);
    rl_replace_line("", 0); // what is 0?
    rl_on_new_line();
    rl_redisplay();
}

void handle_sigint_non_interactive(int sig) {
    g_signal = sig;
    write(1, "\n", 1);
    rl_replace_line("", 0); // what is 0?
    rl_on_new_line();
}

void handle_sigquit_non_interactive(int sig) {
    g_signal = sig;
    write(1, "\n", 1);
    rl_replace_line("Quit (core dumped)", 19);
    rl_on_new_line();
}

void handle_signal(t_shell* shell, t_mode mode) {
    if(g_signal) {
        shell->error_code = g_signal + 128; //TODO exit code
        g_signal = 0;
    }
    if(mode == MODE_NON_INTERACTIVE) {
        signal(SIGINT, &handle_sigint_non_interactive);
        signal(SIGQUIT, &handle_sigquit_non_interactive);
    }
    else if(mode == MODE_INTERACTIVE) {
        signal(SIGINT, &handle_sigint_interactive);
        signal(SIGQUIT, SIG_IGN);
    }
    else if(mode == MODE_HEREDOC) {

    }

    
}