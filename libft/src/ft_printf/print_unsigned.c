/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_unsigned.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:21:09 by ihajji            #+#    #+#             */
/*   Updated: 2024/11/30 09:33:33 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#define BASE 10

static int	print_unsigned_digits(unsigned num, t_flags *f, int len)
{
	char	*buff;
	int		count;
	int		i;

	count = 0;
	i = 0;
	if (!num && f->precision_flag && !f->precision_value)
		return (0);
	buff = malloc(len);
	while (len--)
	{
		buff[i++] = "0123456789"[num % BASE];
		num /= BASE;
	}
	while (i-- > 0)
		count += print(buff[i]);
	free(buff);
	return (count);
}

static int	print_unsigned(unsigned num, t_flags *f, int len)
{
	int	count;

	count = 0;
	if (f->precision_value > len)
		len = f->precision_value;
	if (f->precision_flag)
		f->zero_padded = 0;
	if (f->precision_flag && !f->precision_value && !num)
		len = 0;
	if (!f->left_adjusted)
		count = print_width(f, len);
	count += print_unsigned_digits(num, f, len);
	if (f->left_adjusted)
		count += print_width(f, len);
	return (count);
}

int	handle_unsigned(unsigned int u, t_flags *f)
{
	int	count;
	int	numlen;

	numlen = get_num_len(u, BASE);
	count = print_unsigned(u, f, numlen);
	return (count);
}
