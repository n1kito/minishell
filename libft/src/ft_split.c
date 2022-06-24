/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjallada <mjallada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 15:15:02 by mjallada          #+#    #+#             */
/*   Updated: 2021/12/10 13:12:54 by mjallada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_free_malloc(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

static int	ft_word_counter(char const *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		if (*s != c)
		{
			count++;
			while (*s && *s != c)
				s++;
		}
		else
			s++;
	}
	return (count);
}

static char	*ft_get_next_word(char *s, char c)
{
	while (*s == c)
		s++;
	return (s);
}

static int	ft_word_len(char *s, char c, int len)
{
	while (*s && *s != c)
	{
		len++;
		s++;
	}
	return (len);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		word;
	int		word_len;

	if (!s)
		return (NULL);
	result = malloc(sizeof(char *) * (ft_word_counter(s, c) + 1));
	if (!result)
		return (NULL);
	word = 0;
	while (ft_word_counter(s, c) && *s)
	{
		word_len = 0;
		s = ft_get_next_word((char *)s, c);
		word_len = ft_word_len((char *)s, c, word_len);
		s = s + word_len;
		result[word] = malloc(sizeof(**result) * (word_len + 1));
		if (!result[word])
			return (ft_free_malloc(result));
		ft_strlcpy(result[word++], s - word_len, word_len + 1);
	}
	result[word] = NULL;
	return (result);
}
