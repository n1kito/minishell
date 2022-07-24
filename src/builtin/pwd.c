/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrigaudy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 14:29:06 by vrigaudy          #+#    #+#             */
/*   Updated: 2022/07/24 19:20:14 by vrigaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <unistd.h>
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
		return (-1);
}
