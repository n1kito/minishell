/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrigaudy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 14:29:06 by vrigaudy          #+#    #+#             */
/*   Updated: 2022/08/24 19:44:41 by vrigaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtin.h"
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <limits.h>

int	pwd(void)
{
	char	buffer[PATH_MAX + 1];

	getcwd(buffer, PATH_MAX);
	if (getcwd(buffer, PATH_MAX))
	{
		printf("%s\n", buffer);
		return (0);
	}
	else
	{
		perror("Error: pwd: ");
		return (-1);
	}
}
