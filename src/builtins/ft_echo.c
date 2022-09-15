/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrigaudy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 23:11:50 by vrigaudy          #+#    #+#             */
/*   Updated: 2022/09/16 00:46:58 by vrigaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	echo_option_check(char *str)
{
	int	i;

	i = 0;
	if (!str[i])
		return (0);
	if (str[i] == '-' && str[i + 1])
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

void	ft_echo(char **arg)
{
	int		option_n;
	int		ret;
	int		i;

	g_minishexit = 0;
	i = 1;
	ret = 0;
	option_n = 0;
	if (arg[i])
		option_n = echo_option_check(arg[i]);
	while (arg[i] && echo_option_check(arg[i]))
		i++;
	while (arg[i])
	{
		if (printf("%s", arg[i]) == -1)
			g_minishexit = 1;
		if (arg[i + 1])
			if (printf(" ") == -1)
				g_minishexit = 1;
		i++;
	}
	if (!option_n)
		if (printf("\n") == -1)
			g_minishexit = 1;
}
