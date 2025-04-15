/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 11:32:09 by ihajji            #+#    #+#             */
/*   Updated: 2025/02/17 17:59:05 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_words(const char *s, char c)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			count++;
		while (*s && *s != c)
			s++;
	}
	return (count);
}

static size_t	get_word_len(const char *s, char c)
{
	size_t	len;

	len = 0;
	while (*s && *s != c)
	{
		s++;
		len++;
	}
	return (len);
}

char	**ft_split(char const *s, char c)
{
	size_t	word_count;
	char	**list;
	char	*word;
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
	word_count = count_words(s, c);
	list = ft_calloc(word_count + 1, sizeof(char *));
	if (!list)
		return (NULL);
	while (i < word_count)
	{
		while (*s == c)
			s++;
		word = ft_substr(s, 0, get_word_len(s, c));
		if (!word)
			return ((char **)ft_free_vector(list));
		list[i++] = word;
		while (*s && *s != c)
			s++;
	}
	return (list);
}
