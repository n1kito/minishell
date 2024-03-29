/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjallada <mjallada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:24:00 by mjallada          #+#    #+#             */
/*   Updated: 2022/09/15 14:24:02 by mjallada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Initialises the master structure with correct values. */
void	init_master_structure(t_master *master)
{
	master->cmd_count = 0;
	master->tokens = NULL;
	master->expansions = NULL;
	master->commands = NULL;
	master->processes = NULL;
	master->pipes = NULL;
	master->env_for_exec = NULL;
	master->next_command_start = NULL;
	master->printed_error_msg = 0;
	master->ez_err = 0;
	master->tmp_stdin = -1;
	master->tmp_stdout = -1;
}

/* Frees all malloced variables in the master structure. */
int	free_master(t_master *master, int return_value)
{
	if (master->commands)
		free_commands_structure(master);
	if (master->tokens)
		free_tokens_structure(master);
	if (master->env_for_exec)
		ft_destroy_env(master);
	free_expansions(&master->expansions);
	free_pipes(master);
	free(master->processes);
	master->processes = NULL;
	return (return_value);
}

/* Prints error message on stderr and returns error code passed as parameter. */
int	err_msg(char *error, int error_code, t_master *master)
{
	if (master->printed_error_msg++ == 0)
		ft_printf_fd(2, "\033[1;31mError\033[0;39m\n");
	ft_printf_fd(2, "> %s\n", error);
	return (error_code);
}
