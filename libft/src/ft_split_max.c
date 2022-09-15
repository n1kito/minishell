/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_max.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjallada <mjallada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 23:52:33 by mjallada          #+#    #+#             */
/*   Updated: 2022/09/15 23:52:36 by mjallada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dest, char *src, int size)
{
	int	i;

	i = 0;
	while (src[i] && i < size)
	{
			dest[i] = src[i];
			i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	ft_is_sep(char c, char *sep)
{
	int	i;

	i = 0;
	while (sep[i])
	{
		if (c == sep[i])
			return (1);
		else
				i++;
	}
	return (0);
}

char	*ft_next_sep(char *str, char *sep)
{
	while (*str)
	{
		if (ft_is_sep(*str, sep))
			return (str);
		str++;
	}
	return (str);
}

int	ft_word_count(char *str, char *sep)
{
	int	count;

	count = 0;
	while (*str)
	{
		if (ft_is_sep(*str, sep))
				str++;
		else
		{
			count++;
			str = ft_next_sep(str, sep);
		}
	}
	return (count);
}

char	**ft_split_max(char *str, char *charset)
{
	int		word;
	int		len;
	char	**dest;

	dest = malloc(sizeof(*dest) * (ft_word_count(str, charset) + 1));
	if (!dest)
		return (NULL);
	word = 0;
	while (ft_word_count(str, charset) && *str)
	{
			len = 0;
		while (ft_is_sep(*str, charset))
				str++;
		while ((!(ft_is_sep(*str, charset))) && *str)
		{
			len++;
			str++;
		}
		dest[word] = malloc(sizeof(*dest) * (len + 1));
		if (!dest)
			return (NULL);
		ft_strncpy(dest[word++], str - len, len);
	}
	dest[word] = NULL;
	return (dest);
}
