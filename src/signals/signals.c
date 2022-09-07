#include "minishell.h"

static void	ctrlc_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_minishexit = sig;
	}
}

void	signal_handler(int sig, siginfo_t *siginfo, void *context)
{
	(void)context;
	(void)siginfo;
	signal(SIGQUIT, SIG_IGN);
	ctrlc_handler(sig);
}
