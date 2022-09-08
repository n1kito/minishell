#include "minishell.h"
#include <signals.h>

static void	ctrlc_handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_master->exit_code = 130;
	}
	else if (sig == SIGQUIT)
		printf("\b\b  \b\b");
}

static void	ctrlc_handler_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		g_master->exit_code = 130;
		printf("\n");
		//exit_gnl(g_master, g_master->heredoc_line, 0);
		rl_on_new_line();
		rl_replace_line("", 0);
		close(0);
		//rl_redisplay();
	}
	else if (sig == SIGQUIT)
	{
		ft_putstr_fd("Quit (Core Dumped)\n", 2);
		g_master->exit_code = 131;
		exit(g_master->exit_code);
	}
}

void	signal_handler(int sig, siginfo_t *siginfo, void *context)
{
	(void)context;
	(void)siginfo;
	ctrlc_handler(sig);
}

void	set_heredoc_signal(int sig, siginfo_t *siginfo, void *context)
{
	(void)context;
	(void)siginfo;
	ctrlc_handler_heredoc(sig);
}

void	setup_signals(struct sigaction sa, void (*f)(int, siginfo_t*, void*))
{
	sa.sa_sigaction = f;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}
