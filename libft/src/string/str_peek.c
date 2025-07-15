/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_peek.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 21:54:51 by ihajji            #+#    #+#             */
/*   Updated: 2025/07/15 22:11:17 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

char	str_peek(t_str *str)
{
	if (!str || str->peek >= str->size)
		return ('\0');
	return (str->data[str->peek]);
}

char	str_peek_advance(t_str *str)
{
	if (!str || str->peek >= str->size)
		return ('\0');
	return (str->data[str->peek++]);
}

char	str_peek_reset(t_str *str)
{
	if (!str || !str->size)
		return ('\0');
	str->peek = 0;
	return (str->data[0]);
}

char	str_char_at(t_str *str, size_t i)
{
	if (!str || i >= str->size)
		return ('\0');
	return (str->data[i]);
}
