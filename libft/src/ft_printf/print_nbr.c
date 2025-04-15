/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_nbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:21:09 by ihajji            #+#    #+#             */
/*   Updated: 2024/11/30 09:34:01 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#define BASE 10

static int	handle_nbr_flags(t_flags *f, long num, int len, int sign)
{
	char	*buff;
	int		i;
	int		count;

	count = 0;
	i = 0;
	buff = malloc(len);
	while (len--)
	{
		buff[i++] = "0123456789"[num % BASE];
		num /= BASE;
	}
	if (sign < 0)
		buff[i - 1] = '-';
	else if (f->force_sign && sign > 0)
		buff[i - 1] = '+';
	else if (f->space_flag && sign > 0)
		buff[i - 1] = ' ';
	while (i-- > 0)
		count += print(buff[i]);
	free(buff);
	return (count);
}

static int	print_nbr(long num, t_flags *f, int len, int sign)
{
	int	count;

	count = 0;
	if (f->precision_value > len)
		len = f->precision_value;
	if (f->precision_flag && !f->precision_value && !num)
		len = 0;
	if (sign < 0 || f->force_sign || f->space_flag)
		len += 1;
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
	count += handle_nbr_flags(f, num, len, sign);
	if (f->left_adjusted)
		count += print_width(f, len);
	return (count);
}

int	handle_nbr(int n, t_flags *f)
{
	int		count;
	int		numlen;
	long	num;
	int		sign;

	sign = 1;
	num = n;
	if (n < 0)
	{
		num = -num;
		sign = -sign;
	}
	numlen = get_num_len(num, BASE);
	count = print_nbr(num, f, numlen, sign);
	return (count);
}
