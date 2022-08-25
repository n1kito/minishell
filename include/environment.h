/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrigaudy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 07:27:50 by vrigaudy          #+#    #+#             */
/*   Updated: 2022/08/25 07:38:51 by vrigaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H

# define ENVIRONMENT_H

int	get_env(char **envp, t_env **env);
int	env_for_exe(t_env *env, char **array);

#endif
