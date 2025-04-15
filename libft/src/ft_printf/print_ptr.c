/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:21:09 by ihajji            #+#    #+#             */
/*   Updated: 2024/11/30 09:33:06 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#define BASE 16

static int	print_addr_digits(unsigned long long addr, t_flags *f, int len)
{
	char	*buff;
	int		count;
	int		i;

	count = 0;
	i = len;
	if (f->precision_value > len)
		len = f->precision_value;
	buff = malloc(len);
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
		count += print(buff[i++]);
	free(buff);
	return (count);
}

static int	print_addr(unsigned long long addr, t_flags *f, int len)
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
			count = print_width(f, len);
		}
	}
	count += print_addr_digits(addr, f, len);
	if (f->left_adjusted)
		count += print_width(f, len);
	return (count);
}
// NOTE: precision flag overwrites padding

static int	handle_null_ptr(t_flags *f)
{
	int		count;
	int		nil_len;
	char	*str;

	count = 0;
	f->zero_padded = 0;
	str = "(nil)";
	nil_len = ft_strlen(str);
	if (!f->left_adjusted)
		count += print_width(f, nil_len);
	while (*str)
		print(*(str++));
	count += nil_len;
	if (f->left_adjusted)
		count += print_width(f, nil_len);
	return (count);
}

int	handle_ptr(unsigned long long addr, t_flags *f)
{
	int	count;
	int	numlen;

	numlen = get_num_len(addr, BASE);
	if (!addr)
		count = handle_null_ptr(f);
	else
		count = print_addr(addr, f, numlen);
	return (count);
}
