/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 23:46:23 by zbengued          #+#    #+#             */
/*   Updated: 2025/07/07 23:46:25 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_snprintf_utils.h"
#define BASE 16

static int	print_hex_digits(unsigned int x, t_flags *f, int len, char *hexset, t_buffer *buf)
{
	char	*buff;
	int		count;
	int		i;

	count = 0;
	i = 0;
	if (!x && f->precision_flag && !f->precision_value)
		return (0);
	buff = malloc(len);
	if (!buff)
		return (0); // ou gérer une erreur mémoire si tu veux
	while (len--)
	{
		buff[i++] = hexset[x % BASE];
		x /= BASE;
	}
	if (f->alt_form)
	{
		buff[i - 2] = hexset[BASE];
		buff[i - 1] = '0';
	}
	while (i-- > 0)
		count += sn_print_buffer(buff[i], buf);
	free(buff);
	return (count);
}

static int	print_hexadecimal(unsigned int x, t_flags *f, int len, char *hexset, t_buffer *buf)
{
	int	count;

	count = 0;
	if (f->precision_value > len)
		len = f->precision_value;
	if (f->alt_form && x)
		len += 2;
	if (f->precision_flag && !f->precision_value && !x)
		len = 0;
	if (x == 0)
		f->alt_form = 0;
	if (!f->left_adjusted)
	{
		if (!f->precision_flag && f->zero_padded && f->width > len)
			len = f->width;
		else
		{
			f->zero_padded = 0;
			count = sn_print_width_buf(f, len, buf);
		}
	}
	count += print_hex_digits(x, f, len, hexset, buf);
	if (f->left_adjusted)
		count += sn_print_width_buf(f, len, buf);
	return (count);
}

int	sn_handle_hex(unsigned int x, t_flags *f, char c, t_buffer *buf)
{
	int		count;
	int		numlen;
	char	*hexset;

	if (c == 'x')
		hexset = "0123456789abcdefx";
	else
		hexset = "0123456789ABCDEFX";
	numlen = sn_get_num_len(x, 16);
	count = print_hexadecimal(x, f, numlen, hexset, buf);
	return (count);
}
