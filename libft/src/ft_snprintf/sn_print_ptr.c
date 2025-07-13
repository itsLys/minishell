/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 23:46:44 by zbengued          #+#    #+#             */
/*   Updated: 2025/07/07 23:46:45 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_snprintf_utils.h"
#define BASE 16

static int	print_addr_digits(unsigned long long addr, t_flags *f, int len, t_buffer *buf)
{
	char	*buff;
	int		count;
	int		i;

	count = 0;
	i = len;
	if (f->precision_value > len)
		len = f->precision_value;
	buff = malloc(len);
	if (!buff)
		return (0);
	while (i--)
	{
		buff[i] = "0123456789abcdef"[addr % BASE];
		addr /= BASE;
	}
	if (f->force_sign)
		buff[++i] = '+';
	else if (f->space_flag)
		buff[++i] = ' ';
	buff[++i] = '0';
	buff[++i] = 'x';
	i = 0;
	while (i < len)
		count += sn_print_buffer(buff[i++], buf);
	free(buff);
	return (count);
}

static int	print_addr(unsigned long long addr, t_flags *f, int len, t_buffer *buf)
{
	int	count;

	count = 0;
	if (f->precision_value > len)
		len = f->precision_value;
	len += 2;
	if (f->space_flag || f->force_sign)
		len++;
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
	count += print_addr_digits(addr, f, len, buf);
	if (f->left_adjusted)
		count += sn_print_width_buf(f, len, buf);
	return (count);
}

// NOTE: precision flag overwrites padding

static int	handle_null_ptr(t_flags *f, t_buffer *buf)
{
	int		count;
	int		nil_len;
	char	*str;

	count = 0;
	f->zero_padded = 0;
	str = "(nil)";
	nil_len = ft_strlen(str);
	if (!f->left_adjusted)
		count += sn_print_width_buf(f, nil_len, buf);
	while (*str)
		count += sn_print_buffer(*(str++), buf);
	if (f->left_adjusted)
		count += sn_print_width_buf(f, nil_len, buf);
	return (count);
}

int	sn_handle_ptr(unsigned long long addr, t_flags *f, t_buffer *buf)
{
	int	count;
	int	numlen;

	numlen = sn_get_num_len(addr, BASE);
	if (!addr)
		count = handle_null_ptr(f, buf);
	else
		count = print_addr(addr, f, numlen, buf);
	return (count);
}
