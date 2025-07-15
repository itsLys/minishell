/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_mod1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 20:26:05 by ihajji            #+#    #+#             */
/*   Updated: 2025/07/15 20:34:19 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

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

void	str_append(t_str *str, char *to_add)
{
	size_t	len;

	if (!str || !to_add)
		return ;
	len = ft_strlen(to_add);
	str_ensure_capacity(str, str->size + len);
	ft_memcpy(str->data + str->size, to_add, len);
	str->size += len;
	str->data[str->size] = '\0';
}

void	str_prepend(t_str *str, char *to_add)
{
	size_t	len_toadd;

	if (!str || !to_add)
		return ;
	len_toadd = ft_strlen(to_add);
	str_ensure_capacity(str, str->size + len_toadd);
	ft_memmove(str->data + len_toadd, str->data, str->size + 1);
	ft_memcpy(str->data, to_add, len_toadd);
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

void	str_replace_char(t_str *str, char old_char, char new_char)
{
	size_t	i;

	if (!str || !str->data)
		return ;
	i = 0;
	while (i < str->size)
	{
		if (str->data[i] == old_char)
			str->data[i] = new_char;
		i++;
	}
}
