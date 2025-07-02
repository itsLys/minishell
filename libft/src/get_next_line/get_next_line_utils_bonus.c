/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 14:27:37 by ihajji            #+#    #+#             */
/*   Updated: 2025/06/29 11:48:27 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <get_next_line_bonus.h>

static size_t	count_len_until(const char *s, char c)
{
	size_t	i;

	i = 0;
	if (s)
	{
		while (s[i] && s[i] != c)
			i++;
	}
	if (s && s[i])
		i++;
	return (i);
}

static void	line_append(const char *src, char *dst)
{
	while (*dst)
		dst++;
	if (src)
	{
		while (*src && *src != '\n')
			*(dst++) = *(src++);
		if (*src)
			*(dst++) = '\n';
		*dst = '\0';
	}
}

char	*dup_until(const char *s, char c)
{
	char	*dup;
	int		i;

	dup = malloc(count_len_until(s, c) + 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (*s && *s != c)
		dup[i++] = *(s++);
	if (*s && *s == c)
		dup[i++] = c;
	dup[i] = '\0';
	return (dup);
}

char	*find_chr(const char *s, int c)
{
	if (s)
	{
		c = (char)c;
		while (*s && *s != c)
			s++;
		if (*s == c)
			return ((char *)(s));
	}
	return (NULL);
}

char	*join_reads(char const *s1, char const *s2)
{
	size_t	total_size;
	char	*line;

	total_size = count_len_until(s1, 0) + count_len_until(s2, 0) + 1;
	line = malloc(total_size);
	if (!line)
		return (NULL);
	line[0] = '\0';
	line_append(s1, line);
	line_append(s2, line);
	clean_up((void **) &s1);
	return (line);
}
