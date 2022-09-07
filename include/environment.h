/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrigaudy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 07:27:50 by vrigaudy          #+#    #+#             */
/*   Updated: 2022/09/07 13:56:02 by vrigaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

# include "minishell.h"
# include "tokenizer.h"

int		get_env(char **envp, t_master *master);
int		clean_env(t_env **env, int return_code);
int		env_for_exe(t_master *master);
void	ft_destroy_env(t_master *master);

#endif
