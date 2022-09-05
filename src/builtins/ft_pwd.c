/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrigaudy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 14:29:06 by vrigaudy          #+#    #+#             */
/*   Updated: 2022/09/05 14:20:33 by mjallada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//TODO clean up
#include "minishell.h"

int	ft_pwd(void)
{
	char	buffer[PATH_MAX + 1];

	if (getcwd(buffer, PATH_MAX))
	{
		printf("%s\n", buffer);
		g_minishexit = 0;
		return (0);
	}
	else
	{
		perror("Error: pwd: ");
		g_minishexit = 1;
		return (1);
	}
}