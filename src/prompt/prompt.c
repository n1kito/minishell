/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrigaudy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 14:41:40 by vrigaudy          #+#    #+#             */
/*   Updated: 2022/08/26 23:49:11 by vrigaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include "libft.h"

void	ctrlc_handler(int pid, int sig)
{
	if (pid == 0)
	{
		
	}
	else
	{
		write(2, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		exit(sig);
	}
}

void	ctrlb_handler(int pid, int sig)
{
	if (pid == 0)
	{
		ft_putstr_fd("Quit (core dumped)\n", 2);
		return (sig);
	}
	else
		signal(SIGQUIT, SIG_IGN);
}

void	signal_handler(int sig, siginfo_t *siginfo, void *context)
{
	int	pid;

	(void)context;
	pid = getpid();
	if (sig == SIGINT)
		ctrlc_handler(pid, sig);
	if (sig == SIGQUIT)
		ctrlb_handler(pid, sig);
}

void	read_prompt(void)
{
	char	*line;

	while (1)
	{
		line = readline("🔥🔥🔥MINISHELL🔥🔥🔥 : ");
		if (line)
		{
			add_history(line);
			rl_redisplay();
		}
		if (!line)
			break ;
	}
}

int	main(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = &signal_handler;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	read_prompt();
	return (0);
}
