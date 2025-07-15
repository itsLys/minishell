/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 23:24:19 by zbengued          #+#    #+#             */
/*   Updated: 2025/06/20 00:04:11 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_string.h>

char	str_shift(t_str *str)
{
	char	c;

	if (!str || !str->size)
		return ('\0');
	c = str->data[0];
	ft_memmove(str->data, str->data + 1, str->size);
	str->size--;
	str->data[str->size] = '\0';
	return (c);
}

void	str_shift_by(t_str *str, size_t offset)
{
	if (!str || offset >= str->size)
		return (str_clear(str));
	ft_memmove(str->data, str->data + offset, str->size - offset + 1);
	str->size -= offset;
}

void	str_shift_while(t_str *str, char *charset)
{
	if (!str || !charset)
		return ;
	while (str->size > 0 && ft_strchr(charset, str->data[0]))
		str_shift(str);
}

void	str_segment_set(t_str *str, size_t start, size_t length, size_t end)
{
	char	*ptr;

	if (!str)
		return ;
	ptr = ft_calloc(length + 1, sizeof(char));
	ft_memset(ptr, str_peek(str), length);
	str_segment_remove(str, start, end - start);
	str_insert(str, start, ptr);
}
