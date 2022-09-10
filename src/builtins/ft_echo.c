/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrigaudy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 23:11:50 by vrigaudy          #+#    #+#             */
/*   Updated: 2022/09/10 11:21:55 by mjallada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	echo_option_check(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
	{
		i++;
		while (str[i] && str[i] == 'n')
			i++;
	}
	if (!str[i])
		return (1);
	else
		return (0);
}

int	ft_echo(char **arg)
{
	int	option_n;
	int	i;
	int	ret;

	g_minishexit = 0;
	ret = 0;
	i = 1;
	if (arg[i])
		option_n = echo_option_check(arg[i]);
	else
		option_n = 0;
	while (arg[i] && echo_option_check(arg[i]))
		i++;
	while (arg[i] && ret >= 0)
	{
		ret = write(1, arg[i], ft_strlen(arg[i]));
		if (arg[i + 1] && ret >= 0)
			ret = write(1, " ", 1);
		i++;
	}
	if (!option_n && ret >= 0)
		ret = write(1, "\n", 1);
	if (ret < 0)
		return (0);
	return (1);
}
