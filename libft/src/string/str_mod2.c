/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_mod2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 20:35:44 by ihajji            #+#    #+#             */
/*   Updated: 2025/07/15 20:39:38 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

void	str_surround(t_str *str, size_t start, size_t size, char *to_add)
{
	str_insert(str, start, to_add);
	str_insert(str, size - start, to_add);
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

void	str_repeat(t_str *str, size_t n)
{
	size_t	og_len;
	size_t	i;

	if (!str || !n)
		return ;
	og_len = str->size;
	i = 0;
	str_ensure_capacity(str, n * str->size);
	while (i < n)
		ft_memcpy(str->data + og_len * ++i, str->data, og_len);
	str->size = og_len * n;
	str->data[str->size] = '\0';
}

void	str_clear(t_str *str)
{
	if (!str || !str->data)
		return ;
	str->size = 0;
	str->peek = 0;
	str->data[0] = '\0';
}

void	str_append_char(t_str *str, char c)
{
	char	tmp[2];

	tmp[0] = c;
	tmp[1] = '\0';
	str_append(str, tmp);
}
