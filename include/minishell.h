/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjallada <mjallada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 16:02:51 by mjallada          #+#    #+#             */
/*   Updated: 2022/07/05 18:56:53 by vrigaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

typedef struct	s_env {
	char			*name;
	char			*variable;
	struct s_env	*next;
}				t_env;

void	read_prompt(void);
void	signal_handler(int sig, siginfo_t *siginfo, void *context);

t_env	*get_env(char **envp);

#endif
