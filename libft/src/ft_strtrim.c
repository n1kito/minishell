/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjallada <mjallada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 08:29:44 by mjallada          #+#    #+#             */
/*   Updated: 2021/12/09 11:50:41 by mjallada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_char_is_in_set(char candidate, char *set)
{
	while (*set)
		if (*set++ == candidate)
			return (1);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*output;
	int		len;
	char	*tmp;
	int		i;

	if (!s1 || !set)
		return (NULL);
	len = ft_strlen(s1);
	while (len > 0 && ft_char_is_in_set(*s1++, (char *)set))
		len--;
	s1--;
	tmp = (char *)s1;
	while (*s1)
		s1++;
	s1--;
	while (len > 0 && ft_char_is_in_set(*s1--, (char *)set))
		len--;
	output = malloc(sizeof(*output) * (len + 1));
	if (!output)
		return (NULL);
	i = 0;
	while (i < len)
		output[i++] = *tmp++;
	output[i] = 0;
	return (output);
}
