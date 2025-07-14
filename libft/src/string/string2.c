/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 22:49:21 by zbengued          #+#    #+#             */
/*   Updated: 2025/06/23 17:57:11 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_string.h>

void	str_clear(t_str *str)
{
	if (!str || !str->data)
		return ;
	str->size = 0;
	str->peek = 0;
	str->data[0] = '\0';
}

void	str_insert(t_str *str, size_t pos, char *to_insert)
{
	size_t	insert_len;
	size_t	save_len;

	if (!str || !to_insert || pos > str->size)
		return ;
	insert_len = ft_strlen(to_insert);
	str_ensure_capacity(str, str->size + insert_len);
	save_len = str->size - pos + 1;
	ft_memmove(str->data + pos + insert_len,
		str->data + pos,
		save_len);
	ft_memcpy(str->data + pos, to_insert, insert_len);
	str->size += insert_len;
}

void	str_erase(t_str *str, size_t pos, size_t len)
{
	if (!str || pos >= str->size)
		return ;
	if (pos + len > str->size)
		len = str->size - pos;
	ft_memmove(str->data + pos,
		str->data + pos + len,
		str->size - pos - len + 1);
	str->size -= len;
}

ssize_t	str_find(t_str *str, char *to_find)
{
	char	*found;

	if (!str || !to_find)
		return (-1);
	found = ft_strnstr(str->data, to_find, ft_strlen(str->data));
	if (!found)
		return (-1);
	return ((ssize_t)(found - str->data));
}

void	str_replace(t_str *str, char *old_str, char *new_str, short mode)
{
	size_t	old_len;
	size_t	pos;
	size_t	limit;

	if (!str || !old_str || !new_str || !old_str)
		return ;
	old_len = ft_strlen(old_str);
	pos = 0;
	limit = str->size - old_len;
	while (pos <= limit)
	{
		if (!ft_strncmp(str->data + pos, old_str, old_len))
		{
			str_segment_replace(str, pos, old_len, new_str);
			pos += ft_strlen(new_str);
			if (mode == ONE)
				break ;
		}
		pos++;
	}
}
