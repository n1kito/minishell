#ifndef SIGNALS_H
# define SIGNALS_H

void	signal_handler(int sig, siginfo_t *siginfo, void *context);
void	set_heredoc_signal(int sig, siginfo_t *siginfo, void *context);
void	setup_signals(struct sigaction sa, void (*f)(int, siginfo_t*, void*));

#endif
