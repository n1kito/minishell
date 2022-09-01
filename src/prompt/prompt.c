/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrigaudy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 14:41:40 by vrigaudy          #+#    #+#             */
/*   Updated: 2022/09/01 16:27:31 by vrigaudy         ###   ########.fr       */
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

int	main(void)
{
	t_master			master;
	char				*line;
	struct sigaction	sa;

	line = NULL;
	init_master_master(&master);
	sa.sa_sigaction = &signal_handler;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	while (1)
	{
		line = readline("🔥🔥🔥MINISHELL🔥🔥🔥 : ");
		if (line)
		{
			add_history(line);
			rl_redisplay();
			execute_command(line, &master);
		}
		if (!line)
		{
			write(1, "exit\n", 5);
			break ;
		}
	}
	return (0);
}
