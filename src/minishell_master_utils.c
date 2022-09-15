/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_master_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjallada <mjallada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:24:22 by mjallada          #+#    #+#             */
/*   Updated: 2022/09/15 14:24:24 by mjallada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_all(t_master *master, int return_code)
{
	clean_env(&master->env, 0);
	free_master(master, 0);
	free(master->exit_code);
	rl_clear_history();
	return (return_code);
}

/* Goes through the tokens and frees every node. */
void	free_tokens_structure(t_master *master)
{
	t_tokens	*current;
	t_tokens	*next_token;

	current = master->tokens;
	while (current)
	{
		next_token = current->next;
		free(current->token);
		free(current);
		current = next_token;
	}
	master->tokens = NULL;
}

/* Frees memory allocated for storing the command arrays but not for the command
 * themselves. These are freed separately when freeing the tokens list. */
void	free_commands_structure(t_master *master)
{
	int	i;

	i = 0;
	while (master->commands && master->commands[i])
	{
		if (master->commands[i]->heredoc_fd >= 0)
			close(master->commands[i]->heredoc_fd);
		if (master->commands[i]->cmd_path
			&& master->commands[i]->cmd_path
			!= master->commands[i]->cmd_array[0])
			free(master->commands[i]->cmd_path);
		free(master->commands[i]->cmd_array);
		free(master->commands[i]->heredoc_path);
		if (master->commands[i]->fds)
			free(master->commands[i]->fds);
		free(master->commands[i++]);
	}
	free(master->commands);
	master->commands = NULL;
}

void	free_pipes(t_master *master)
{
	int	i;

	i = 0;
	if (!master->pipes)
		return ;
	while (i < master->cmd_count - 1)
	{
		free(master->pipes[i]);
		master->pipes[i] = NULL;
		i++;
	}
	free(master->pipes);
	master->pipes = NULL;
}
