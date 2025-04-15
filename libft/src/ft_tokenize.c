/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 11:32:09 by ihajji            #+#    #+#             */
/*   Updated: 2025/03/02 00:02:50 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_qoute_len(const char *s)
{
	char	qoute;
	size_t	i;

	qoute = *s;
	i = 0;
	i++;
	while (s[i] && s[i] != qoute)
		i++;
	if (s[i] == qoute)
		i++;
	return (i);
}

static size_t	get_token_len(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] && !(s[i] == ' ' || s[i] == '\t'))
	{
		if (s[i] == '"' || s[i] == '\'')
			i += get_qoute_len(&s[i]);
		if (s[i] == '\\')
			i++;
		if (s[i])
			i++;
	}
	return (i);
}

static size_t	count_tokens(const char *s)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		while (*s && (*s == ' ' || *s == '\t') && !(*s == '"' || *s == '\''))
			s++;
		count++;
		if (*s == '"' || *s == '\'')
			s += get_qoute_len(s);
		s += get_token_len(s);
	}
	return (count);
}

static char	**free_mem(char **list, size_t i)
{
	while (i-- > 0)
		free(list[i]);
	free(list);
	return (NULL);
}

char	**ft_tokenize(char const *s)
{
	size_t	token_count;
	char	**list;
	char	*token;
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
	token_count = count_tokens(s);
	list = ft_calloc(token_count + 1, sizeof(char *));
	if (!list)
		return (NULL);
	while (i < token_count)
	{
		while (*s == ' ' || *s == '\t')
			s++;
		token = ft_substr(s, 0, get_token_len(s));
		if (!token)
			return (free_mem(list, i));
		list[i++] = token;
		s += get_token_len(s);
	}
	return (list);
}
