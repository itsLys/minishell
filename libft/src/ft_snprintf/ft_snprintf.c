/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_snprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:42:31 by ihajji            #+#    #+#             */
/*   Updated: 2025/07/08 00:09:10 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_snprintf_utils.h"

static int	handle_fmt(const char *fmt, va_list args, t_buffer *buffer)
{
	t_flags	f;
	int		count = 0;

	while (*fmt)
	{
		if (*fmt != '%')
			count += sn_print_buffer(*(fmt++), buffer);
		else if (sn_check_valid(++fmt))
		{
			sn_parse_fmt(fmt, args, &f, buffer);
			fmt += f.total;
			if (f.printed == -1)
				return (-1);
			count += f.printed;
		}
		else
			count += sn_print_buffer('%', buffer);
	}
	if (sn_catch_err(0) == -1)
		return (-1);
	return (count);
}

int	ft_snprintf(char *str, size_t size, const char *fmt, ...)
{
	int			count;
	va_list		args;
	t_buffer	buffer;

	if (!fmt)
		return (-1);
	buffer.buf = str;
	buffer.size = size;
	buffer.pos = 0;
	va_start(args, fmt);
	count = handle_fmt(fmt, args, &buffer);
	va_end(args);
	if (size > 0)
	{
		if ((size_t)buffer.pos < size)
			buffer.buf[buffer.pos] = '\0';
		else
			buffer.buf[size - 1] = '\0';
	}
	return (count);
}
