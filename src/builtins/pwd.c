/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrigaudy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 14:29:06 by vrigaudy          #+#    #+#             */
/*   Updated: 2022/08/31 13:54:58 by vrigaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtin.h"
#include "libft.h"
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <limits.h>

int	pwd(char **arg)
{
	char	buffer[PATH_MAX + 1];

	if (arg[1])
	{
		ft_putstr_fd("pwd: too many arguments", 2);
		return (1);
	}
	getcwd(buffer, PATH_MAX);
	if (getcwd(buffer, PATH_MAX))
	{
		printf("%s\n", buffer);
		return (0);
	}
	else
	{
		perror("Error: pwd: ");
		return (1);
	}
}