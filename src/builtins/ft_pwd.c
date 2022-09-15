/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrigaudy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 14:29:06 by vrigaudy          #+#    #+#             */
/*   Updated: 2022/09/12 16:33:44 by vrigaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(void)
{
	char	buffer[PATH_MAX + 1];

	if (getcwd(buffer, PATH_MAX))
	{
		printf("%s\n", buffer);
		g_minishexit = 0;
	}
	else
	{
		perror("Error: pwd: ");
		g_minishexit = 1;
	}
}
