/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   321string6.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 09:40:02 by zbengued          #+#    #+#             */
/*   Updated: 2025/07/15 20:21:27 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_string.h>

size_t	str_segments_count(t_str *str, char delimiter)
{
	size_t	count;
	size_t	i;

	if (!str || !str->size)
		return (0);
	count = 0;
	i = 0;
	while (i < str->size)
	{
		while (i < str->size && str->data[i] == delimiter)
			i++;
		if (i < str->size)
		{
			count++;
			while (i < str->size && str->data[i] != delimiter)
				i++;
		}
	}
	return (count);
}

// t_str	str_substr(t_str *str, size_t start, size_t len)
// {
// 	t_str	sub;
//
// 	str_init(&sub);
// 	if (!str || start >= str->size)
// 		return (sub);
// 	if (start + len > str->size)
// 		len = str->size - start;
// 	str_ensure_capacity(&sub, len);
// 	ft_memcpy(sub.data, str->data + start, len);
// 	sub.data[len] = '\0';
// 	sub.size = len;
// 	return (sub);
// }

static void	str_fill_split(t_str *str, char d, t_str *arr, size_t c)
{
	size_t	i;
	size_t	start;
	size_t	part;

	i = 0;
	start = 0;
	part = 0;
	while (i <= str->size && part < c)
	{
		if (i == str->size || str->data[i] == d)
		{
			if (i > start)
				arr[part++] = str_substr(str, start, i - start);
			while (i < str->size && str->data[i] == d)
				i++;
			start = i;
		}
		else
			i++;
	}
}

t_str	*str_split(t_str *s, char delimiter, size_t *count)
{
	t_str	*parts;

	if (!s || !count)
		return (NULL);
	*count = str_segments_count(s, delimiter);
	if (*count == 0)
		return (NULL);
	parts = ft_calloc((*count), sizeof(t_str));
	if (!parts)
		return (NULL);
	str_fill_split(s, delimiter, parts, *count);
	return (parts);
}
