/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrigaudy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 14:41:40 by vrigaudy          #+#    #+#             */
/*   Updated: 2022/07/01 17:13:40 by vrigaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// This function creates a prompt and stores all the inputs given
// The list of commands can be accessed by pressing the up and down arrows

void	read_prompt(void)
{
	char				*line;
	struct sigaction	sa;

	sa.sa_sigaction = &signal_handler;
	sa.sa_flags = SA_RESTART;
	while (1)
	{
		line = readline("🔥🔥🔥MINISHELL🔥🔥🔥 : ");
		if (line)
		{
			add_history(line);
			rl_redisplay();
		}
		free(line);
	}
}
