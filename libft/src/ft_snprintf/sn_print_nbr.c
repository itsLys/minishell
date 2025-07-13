/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_nbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 23:46:36 by zbengued          #+#    #+#             */
/*   Updated: 2025/07/07 23:46:38 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_snprintf_utils.h"
#define BASE 10

static int	handle_nbr_flags(t_flags *f, long num, int len, int sign, t_buffer *buf)
{
	char	*buff;
	int		i;
	int		count;

	count = 0;
	i = 0;
	buff = malloc(len);
	if (!buff)
		return (0);
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
		count += sn_print_buffer(buff[i], buf);
	free(buff);
	return (count);
}

static int	print_nbr(long num, t_flags *f, int len, int sign, t_buffer *buf)
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
			count = sn_print_width_buf(f, len, buf);
		}
	}
	count += handle_nbr_flags(f, num, len, sign, buf);
	if (f->left_adjusted)
		count += sn_print_width_buf(f, len, buf);
	return (count);
}

int	sn_handle_nbr(int n, t_flags *f, t_buffer *buf)
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
	numlen = sn_get_num_len(num, BASE);
	count = print_nbr(num, f, numlen, sign, buf);
	return (count);
}
