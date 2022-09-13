/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrigaudy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 10:24:37 by vrigaudy          #+#    #+#             */
/*   Updated: 2022/09/13 00:19:25 by vrigaudy         ###   ########.fr       */
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
		g_minishexit = 130;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
		ft_putstr_fd("\b\b  \b\b", 0);
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
		g_minishexit = 130;
		printf("\n");
	}
	if (sig == SIGQUIT)
		g_minishexit = 131;
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	setup_signals(struct sigaction sa, void (*f)(int, siginfo_t*, void*))
{
	sigemptyset(&sa.sa_mask);
	sa.sa_sigaction = f;
	sa.sa_flags = SA_RESTART;
	//signal(SIGPIPE, SIG_IGN);
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	//sigaction(SIGPIPE, &sa, NULL);
}
