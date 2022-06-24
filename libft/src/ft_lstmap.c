/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjallada <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 14:13:35 by mjallada          #+#    #+#             */
/*   Updated: 2021/12/08 16:31:26 by mjallada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void(*del)(void *))
{
	t_list	*out;
	t_list	*first_elem;

	if (!lst)
		return (NULL);
	out = ft_lstnew(f(lst->content));
	if (!out)
		return (NULL);
	first_elem = out;
	lst = lst->next;
	while (lst)
	{
		out->next = ft_lstnew(f(lst->content));
		if (!out)
		{
			ft_lstclear(&first_elem, del);
			return (NULL);
		}
		lst = lst->next;
		out = out->next;
	}
	return (first_elem);
}
