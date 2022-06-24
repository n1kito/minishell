/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjallada <mjallada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 16:00:32 by mjallada          #+#    #+#             */
/*   Updated: 2021/12/08 15:53:15 by mjallada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t		i;
	char		*newstr;
	size_t		len2;

	i = 0;
	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	len2 = ft_strlen(s + start);
	if (len2 > len)
		len2 = len;
	newstr = malloc(sizeof(*newstr) * (len2 + 1));
	if (!newstr)
		return (NULL);
	while (s[start] && i < len)
		newstr[i++] = s[start++];
	newstr[i] = 0;
	return (newstr);
}
