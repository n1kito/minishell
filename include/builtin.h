/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrigaudy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 19:30:51 by vrigaudy          #+#    #+#             */
/*   Updated: 2022/08/24 15:49:41 by vrigaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H

# define BUILTIN_H

//fonctions our les builtins
int		pwd(void);
int		env(t_env *env);
int		echo(char **arg);
int		cd(char *path, t_env *env);
int		unset(t_env *env, char *str);
int		ft_export(t_env *env, char **variable);
int		ft_exit(t_master *master);

//utils pour les builtins
char	*add_name(char *str, int i);
char	*add_variable(char *str, int i, int j);

#endif
