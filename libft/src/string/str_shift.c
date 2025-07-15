/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_shift.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 21:56:27 by ihajji            #+#    #+#             */
/*   Updated: 2025/07/15 21:57:06 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

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
