/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_no_arg.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjallada <mjallada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 23:51:52 by mjallada          #+#    #+#             */
/*   Updated: 2022/09/15 23:51:54 by mjallada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

static int	is_sorted_list(t_env *list[])
{
	int	i;

	i = 0;
	while (list[i + 1])
	{
		if (ft_strcmp(list[i]->name, list[i + 1]->name) < 0)
			i++;
		else
			return (0);
	}
	return (1);
}

static int	lstlen(t_env *list)
{
	int	i;

	i = 0;
	while (list)
	{
		i++;
		list = list->next;
	}
	return (i);
}

static void	sort_table_alphabetically(t_env **sorting_table, int list_len)
{
	int		i;
	t_env	*tmp;

	i = 0;
	while (!is_sorted_list(sorting_table))
	{
		if (ft_strcmp(sorting_table[i]->name, sorting_table[i + 1]->name) > 0)
		{
			tmp = sorting_table[i];
			sorting_table[i] = sorting_table[i + 1];
			sorting_table[i + 1] = tmp;
		}
		i++;
		if (i > list_len - 2)
			i = 0;
	}
}

/* Populates the sorting table with the address of each node of the environment
 * list. */
static void	populate_sorting_table(t_env *list, t_env **sort_tab, int list_len)
{
	int		i;
	t_env	*current;

	i = 0;
	current = list;
	while (i < list_len)
	{
		sort_tab[i] = current;
		i++;
		current = current->next;
	}
}

/* Takes the environment linked list and creates a sorting table that stores
 * each one of its nodes, so they can easily be swapped to sort by name
 * variables without affecting the actual environment list. Then the table is
 * sorted and the list is printed. Table is then freed. */
void	print_env_by_alphabetical_order(t_env *list)
{
	int		i;
	int		list_len;
	t_env	**sorting_table;

	list_len = lstlen(list);
	sorting_table = malloc(sizeof(t_env *) * (list_len + 1));
	sorting_table[list_len] = NULL;
	populate_sorting_table(list, sorting_table, list_len);
	sort_table_alphabetically(sorting_table, list_len);
	i = -1;
	while (sorting_table[++i])
	{
		safe_printf(sorting_table[i]->name);
		if (sorting_table[i]->is_env)
		{
			safe_printf("=\"");
			if (sorting_table[i]->variable && sorting_table[i]->variable[0])
				safe_printf(sorting_table[i]->variable);
			safe_printf("\"");
		}
		safe_printf("\n");
	}
	free(sorting_table);
}
