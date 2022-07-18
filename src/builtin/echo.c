/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrigaudy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 23:11:50 by vrigaudy          #+#    #+#             */
/*   Updated: 2022/07/18 23:49:53 by vrigaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"

int	echo_option_check(char *str)
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

int	echo(char **arg)
{
	int	n;
	int	check;
	int	i;

	i = 1;
	n = echo_option_check(arg[i]);
	check = n;
	while (n == 1)
	{
		i++;
		n = echo_option_check(arg[i]);
	}
	while (arg[i])
	{
		printf("%s", arg[i]);
		if (arg[i + 1])
			printf(" ");
		i++;
	}
	if (!check)
		printf("\n");
	return (0);
}

int	main(int argc, char **argv)
{
	echo(argv);
	return (0);
}
