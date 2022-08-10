/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrigaudy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 15:03:26 by vrigaudy          #+#    #+#             */
/*   Updated: 2022/08/10 19:38:28 by vrigaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtin.h"

char	*add_variable(char *str, int i, int j)
{
	char	*variable;

	if (i == 0 || j == 0 || j - i <= 0)
		return (NULL);
	variable = malloc(sizeof(char) * j - i + 1);
	if (!variable)
		return (NULL);
	while (*(str - 1) != '=')
		str++;
	ft_strlcpy(variable, str, j - i);
	return (variable);
}

char	*add_name(char *str, int i)
{
	char	*name;

	if (i == 0)
		return (NULL);
	name = malloc(sizeof(char) * (i + 1));
	if (!name)
		return (NULL);
	ft_strlcpy(name, str, i);
	return (name);
}
