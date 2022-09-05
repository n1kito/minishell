/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrigaudy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 23:11:50 by vrigaudy          #+#    #+#             */
/*   Updated: 2022/09/05 10:59:44 by vrigaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtin.h"

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

void	echo(char **arg)
{
	int	n;
	int	i;
	int	ret;

	ret = 0;
	i = 1;
	if arg[i]
		n = echo_option_check(arg[i]);
	else
		n = 0;
	while (arg[i] && echo_option_check(arg[i]))
		i++;
	while (arg[i] && ret == 0)
	{
		ret = write(1, arg[i], ft_strlen(arg[i]));
		if (arg[i + 1] && ret == 0)
			ret = write(1, " ", 1);
		i++;
	}
	if (!n)
		ret = write(1, "\n", 1);
	g_minishexit = -ret;
}
