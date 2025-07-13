/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 23:47:17 by zbengued          #+#    #+#             */
/*   Updated: 2025/07/07 23:47:18 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_snprintf_utils.h"

int	sn_print_buffer(char c, t_buffer *buf)
{
	if ((size_t)buf->pos < buf->size)
		buf->buf[buf->pos] = c;
	buf->pos++;
	return (1);
}

int	sn_print_width_buf(t_flags *f, int n, t_buffer *buf)
{
	int	count;

	count = 0;
	while (f->width - n > 0)
	{
		if (f->zero_padded)
			count += sn_print_buffer('0', buf);
		else
			count += sn_print_buffer(' ', buf);
		f->width--;
	}
	return (count);
}

int	sn_get_num_len(unsigned long long n, unsigned int base)
{
	int	len;

	len = 1;
	while (n > base - 1)
	{
		n /= base;
		len++;
	}
	return (len);
}

int	sn_check_valid(const char *fmt)
{
	while (*fmt && ft_strchr(FLAGS, *fmt))
		fmt++;
	while (*fmt && ft_isdigit(*fmt))
		fmt++;
	if (*fmt == '.')
		fmt++;
	while (*fmt && ft_isdigit(*fmt))
		fmt++;
	if (ft_strchr(CONVERSIONS, *fmt))
		return (1);
	return (0);
}

int	sn_catch_err(int n)
{
	static int	e;

	if (n == -1 && e == 0)
		e = -1;
	return (e);
}
