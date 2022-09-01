/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrigaudy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 13:31:58 by vrigaudy          #+#    #+#             */
/*   Updated: 2022/09/01 14:14:40 by vrigaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void	ctrlc_handler(int pid, int sig)
{
	if (sig == SIGINT)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		exit(sig);
	}
}

void	signal_handler(int sig, siginfo_t *siginfo, void *context)
{
	int	pid;

	(void)context;
	pid = getpid();
	signal(SIGQUIT, SIG_IGN);
	ctrlc_handler(pid, sig);
}
