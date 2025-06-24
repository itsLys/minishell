/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string7.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 10:04:49 by zbengued          #+#    #+#             */
/*   Updated: 2025/06/24 04:57:05 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_string.h>

void	str_create(t_str *str, char *text)
{
	str_init(str);
	str_set(str, text);
}

static size_t	str_total_size(t_str *arr, size_t len, size_t delim_len)
{
	size_t	total;
	size_t	i;

	total = 0;
	i = 0;
	while (i < len)
	{
		total += arr[i].size;
		if (i < len - 1)
			total += delim_len;
		i++;
	}
	return (total);
}

static void	str_fill(t_str *result, t_str *arr, size_t len, char *d)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		str_append(result, arr[i].data);
		if (i < len - 1 && d)
			str_append(result, d);
		i++;
	}
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
