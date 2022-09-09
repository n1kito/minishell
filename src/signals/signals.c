/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrigaudy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 10:24:37 by vrigaudy          #+#    #+#             */
/*   Updated: 2022/09/09 14:02:50 by mjallada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signals.h>

void	signal_handler(int sig, siginfo_t *siginfo, void *context)
{
	(void)context;
	(void)siginfo;
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_minishexit = 130;
	}
	else if (sig == SIGQUIT)
		printf("\b\b  \b\b");
}

void	set_heredoc_signal(int sig, siginfo_t *siginfo, void *context)
{
	(void)context;
	(void)siginfo;
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		//rl_replace_line("", 0);
		g_minishexit = 130;
		close(0);
	}
	else if (sig == SIGQUIT)
		ft_putstr_fd("\b\b  \b\b", 0);
}

void	set_command_signal(int sig, siginfo_t *siginfo, void *context)
{
	(void)context;
	(void)siginfo;
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		g_minishexit = 130;
	}
	else if (sig == SIGQUIT)
	{
		ft_putstr_fd("Quit (Core Dumped)\n", 2);
		g_minishexit = 131;
	}
}

void	setup_signals(struct sigaction sa, void (*f)(int, siginfo_t*, void*))
{
	sigemptyset(&sa.sa_mask);
	sa.sa_sigaction = f;
	sa.sa_flags = SA_RESTART;
	//signal(SIGPIPE, SIG_IGN); // added by mj to be able to handle SIGPIPES, mais pense qu'on doit quand mem les eviter.
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}
