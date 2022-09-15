/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrigaudy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 23:11:50 by vrigaudy          #+#    #+#             */
/*   Updated: 2022/09/14 17:54:00 by vrigaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*swap_pointers_for_join(char *buffer, char *str, t_master *master)
{
	char	*tmp;
	int		command;

	command = master->cmd_count;
	tmp = NULL;
	tmp = buffer;
	if (!buffer)
		buffer = ft_strdup(str);
	else
		buffer = ft_strjoin(buffer, str);
	if (!buffer)
	{
		if (tmp)
			free(tmp);
		write(2, "Minishell failure: malloc error in builtin: echo\n", 50);
		free_all(master, g_minishexit);
		if (command > 1)
			exit(42);
		exit(1);
	}
	free(tmp);
	return (buffer);
}

static char	*join_message_for_write(char **message, t_master *master)
{
	char	*buffer;
	int		command;

	command = master->cmd_count;
	if (!message || !*message || !**message)
		return (NULL);
	buffer = malloc(ft_strlen(*message) + 1);
	if (!buffer && message && *message)
	{
		write(2, "Minishell failure: malloc error in builtin: echo\n", 50);
		if (command > 1)
			exit(free_all(master, 42));
		exit(free_all(master, 1));
	}
	ft_strlcpy(buffer, *message, ft_strlen(*message) + 1);
	message++;
	while (*message && **message)
	{
		if (message + 1)
			buffer = swap_pointers_for_join(buffer, " ", master);
		buffer = swap_pointers_for_join(buffer, *message, master);
		message++;
	}
	return (buffer);
}

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

void	ft_echo(char **arg, t_master *master)
{
	int		option_n;
	int		ret;
	int		i;
	char	*buffer;

	g_minishexit = 0;
	i = 1;
	ret = 0;
	buffer = NULL;
	option_n = 0;
	if (arg[i])
		option_n = echo_option_check(arg[i]);
	else
		option_n = 0;
	while (arg[i] && echo_option_check(arg[i]))
		i++;
	buffer = join_message_for_write(&arg[i], master);
	if (!option_n)
		buffer = swap_pointers_for_join(buffer, "\n", master);
	ret = write(1, buffer, ft_strlen(buffer));
	if (ret == -1)
		g_minishexit = 1;
	free(buffer);
}
