/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrigaudy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 19:30:51 by vrigaudy          #+#    #+#             */
/*   Updated: 2022/09/04 17:00:22 by mjallada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H

# define BUILTIN_H

//fonctions our les builtins
int		ft_pwd(void);
int		ft_env(t_env *env);
int		ft_echo(char **arg);
int		ft_cd(char **path, t_env *env);
int		ft_unset(t_env *env, char **arg);
int		ft_export(t_env **env, char **variable);
//int		ft_exit(t_master *master);

//utils pour les builtins
int		arg_is_ok_for_env(char const *str);

#endif
