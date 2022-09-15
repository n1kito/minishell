/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjallada <mjallada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:36:03 by mjallada          #+#    #+#             */
/*   Updated: 2022/09/15 14:36:04 by mjallada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// INCLUDES
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <limits.h>
# include "libft.h"
# include "environment.h"
# include "tokenizer.h"
# include "builtins.h"
# include "parser.h"
# include "execution.h"
# include "signals.h"

extern int	g_minishexit;

// main.c
int		found_open_quotes(t_master *master);
int		execute_command(char *command_line, t_master *master);
void	read_prompt(t_master *master);

// minishell_utils.c
void	init_master_structure(t_master *master);
int		free_master(t_master *master, int return_value);
int		err_msg(char *error, int error_code, t_master *master);

// minishell_master_utils.c
int		free_all(t_master *master, int return_code);
void	free_tokens_structure(t_master *master);
void	free_commands_structure(t_master *master);
void	free_pipes(t_master *master);

#endif
