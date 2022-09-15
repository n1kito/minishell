/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjallada <mjallada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 13:45:28 by mjallada          #+#    #+#             */
/*   Updated: 2022/09/13 00:13:50 by vrigaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_minishexit = 0;

/* Goes through all tokens and returns 0 if an unclosed quote was found. */
int	found_open_quotes(t_master *master)
{
	t_tokens	*current;

	current = master->tokens;
	while (current)
	{
		if (has_solitary_quote(current->token, master))
		{
			g_minishexit = 2;
			return (1);
		}
		current = current->next;
	}
	return (0);
}

int	execute_command(char *command_line, t_master *master)
{
	if (command_line == NULL)
		return (0);
	init_tokenizer_helpers(&master->helpers, command_line);
	tokenizer(command_line, master, &master->helpers);
	parser(&master->tokens);
	if (found_open_quotes(master))
		return (1);
	expander(master);
	if (!syntax_checker(master->tokens, master, master->ez_err))
		return (1);
	prep_execution_resources(master);
	if (heredoc_found(master) && (g_minishexit == 130))
	{
		if (!unlink_heredocs(master))
			return (0);
		return (1);
	}
	if (master->cmd_count == 1
		&& is_builtin_function(master->commands[0]->cmd_array[0]))
		execute_single_builtin(master);
	else if (!exec_loop(master))
		return (0);
	return (1);
}

void	read_prompt(t_master *master)
{
	char	*line;

	line = NULL;
	while (1)
	{
		if (g_minishexit == 0)
			line = readline("🔥 mini\033[2ms\033[0mhell \033[0;31m>\033[0;39m ");
		else
			line = readline("☠️  mini\033[2ms\033[0mhell \033[0;31m>\033[0;39m ");
		if (line && line[0])
		{
			add_history(line);
			init_master_structure(master);
			if (!execute_command(line, master))
				exit(free_all(master, 1));
			free_master(master, 1);
//			sigemptyset(&new_action.sa_mask);
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

	if (argc != 1)
		return (1);
	(void)argc;
	(void)argv;
	master.env = NULL;
	master.sa = &sa;
	master.exit_code = NULL;
	get_env(envp, &master);
	init_master_structure(&master);
	setup_signals(sa, &signal_handler);
	read_prompt(&master);
	return (free_all(&master, g_minishexit));
}
