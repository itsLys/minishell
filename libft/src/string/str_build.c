/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_build.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 20:19:26 by ihajji            #+#    #+#             */
/*   Updated: 2025/07/15 20:24:33 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

void	str_set(t_str *str, char *new_data)
{
	size_t	new_len;

	if (!str || !new_data)
		return ;
	new_len = ft_strlen(new_data);
	str_ensure_capacity(str, new_len);
	ft_memcpy(str->data, new_data, new_len);
	str->data[new_len] = '\0';
	str->size = new_len;
	str->peek = 0;
}

t_str	str_new_fill(size_t size, char c)
{
	t_str	str;
	size_t	i;

	str_init(&str);
	str_ensure_capacity(&str, size + 1);
	i = 0;
	while (i < size)
	{
		str.data[i] = c;
		i++;
	}
	str.size = size;
	return (str);
}

t_str	str_substr(t_str *str, size_t start, size_t len)
{
	t_str	sub;

	str_init(&sub);
	if (!str || start >= str->size)
		return (sub);
	if (start + len > str->size)
		len = str->size - start;
	str_ensure_capacity(&sub, len);
	ft_memcpy(sub.data, str->data + start, len);
	sub.data[len] = '\0';
	sub.size = len;
	return (sub);
}

t_str	str_join(t_str *array, size_t len, char *delimiter)
{
	t_str	result;
	size_t	delim_len;
	size_t	total;

	str_init(&result);
	if (!array || len == 0)
		return (result);
	delim_len = 0;
	if (delimiter)
		delim_len = ft_strlen(delimiter);
	total = str_total_size(array, len, delim_len);
	str_ensure_capacity(&result, total);
	str_fill(&result, array, len, delimiter);
	return (result);
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
