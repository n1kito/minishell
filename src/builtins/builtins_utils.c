#include "../../include/builtins.h"

/* Compares two strings, returns 0 if they are identical, otherwise returns
 * difference between the first two different characters. */
int	ft_strcmp(const char *first, const char *second)
{
	size_t			i;
	unsigned char	*c1;
	unsigned char	*c2;

	i = 0;
	c1 = (unsigned char *)first;
	c2 = (unsigned char *)second;
	if (!c1 || !c2)
		return (0);
	while (c1[i] && c2[i])
	{
		if (c1[i] != c2[i])
			return (c1[i] - c2[i]);
		i++;
	}
	return (0);
}

/* Checks the sorting table and returns 1 if all name variables in each node
 * are sorted. */
// TODO: Clearup this description maybe
int	is_sorted_list(t_env *list[])
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

/* Returns len of a given linked list. */
// TODO: Use ft_lstsize from the libft instead.
int	lstlen(t_env *list)
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
