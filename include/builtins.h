/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjallada <mjallada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:35:42 by mjallada          #+#    #+#             */
/*   Updated: 2022/09/16 04:10:38 by vrigaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

// fonctions our les builtins
void	ft_pwd(void);
void	ft_env(t_env *env, char **arg);
void	ft_echo(char **arg);
void	ft_cd(t_master *master, char **path);
void	ft_unset(t_env **env, char **arg);
void	ft_export(t_master *master, char **variable);
void	ft_exit(t_master *master, int cmd_index);

// utils pour les builtins
void	print_env_by_alphabetical_order(t_env *list, t_master *master);
int		arg_is_ok_for_env(char const *str, int exprt);
void	check_malloc_in_builtin(t_master *master, t_env *env);
void	safe_printf(char *to_print);
void	exit_env_printer(t_master *master);
int		ft_strcmp2(char *s1, char *s2);

#endif
