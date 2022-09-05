
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjallada <mjallada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 13:45:28 by mjallada          #+#    #+#             */
/*   Updated: 2022/09/02 12:56:18 by mjallada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_minishexit = 0;

int	execute_command(char *command_line, t_master *master)
{
	if (command_line == NULL)
		return (0);
	init_tokenizer_helpers(&master->helpers, command_line);
	if (!tokenizer(command_line, master, &master->helpers)
		|| !parser(&master->tokens)
		|| !expander(master)
		|| !syntax_checker(master)
		|| !prep_execution_resources(master))
			return (0);
	if (master->cmd_count == 1
		&& is_builtin_function(master->commands[0]->cmd_array[0]))
	{
		if(!execute_single_builtin(master))
			return (0);
	}
	else if (!exec_loop(master))
		return (0);
	free_master(master, 1);
	return (1);
}

void	read_prompt(t_master *master)
{
	char	*line;

	line = NULL;
	while (1)
	{
		line = readline("mini🔥hell \033[0;31m>\033[0;39m ");
		if (line)
		{
			add_history(line);
			if (!execute_command(line, master))
				free_master(master, 1);
			//rl_redisplay();
		}
		if (!line)
		{
			write(1, "exit\n", 5);
			break ;
		}
		free(line);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_master			master;
	struct sigaction	sa;

	(void)argc;
	(void)argv;
	init_master_structure(&master, envp);
	sa.sa_sigaction = &signal_handler;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	read_prompt(&master);
	return (free_master(&master, 0));
}
