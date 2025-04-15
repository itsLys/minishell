/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:21:09 by ihajji            #+#    #+#             */
/*   Updated: 2025/02/17 22:51:15 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#define BASE 16

static int	print_hex_digits(unsigned int x, t_flags *f, int len, char *hexset)
{
	char	*buff;
	int		count;
	int		i;

	count = 0;
	i = 0;
	if (!x && f->precision_flag && !f->precision_value)
		return (0);
	buff = malloc(len);
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
		count += print(buff[i]);
	free(buff);
	return (count);
}

static int	print_hexadecimal(unsigned int x, t_flags *f, int len, char *hexset)
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
			count = print_width(f, len);
		}
	}
	count += print_hex_digits(x, f, len, hexset);
	if (f->left_adjusted)
		count += print_width(f, len);
	return (count);
}

int	handle_hex(unsigned int x, t_flags *f, char c)
{
	int		count;
	int		numlen;
	char	*hexset;

	if (c == 'x')
		hexset = "0123456789abcdefx";
	else
		hexset = "0123456789ABCDEFX";
	numlen = get_num_len(x, 16);
	count = print_hexadecimal(x, f, numlen, hexset);
	return (count);
}
