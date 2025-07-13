/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_unsigned.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 23:47:08 by zbengued          #+#    #+#             */
/*   Updated: 2025/07/07 23:47:09 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_snprintf_utils.h"
#define BASE 10

static int	print_unsigned_digits(unsigned num, t_flags *f, int len, t_buffer *buf)
{
	char	*buff;
	int		count;
	int		i;

	count = 0;
	i = 0;
	if (!num && f->precision_flag && !f->precision_value)
		return (0);
	buff = malloc(len);
	if (!buff)
		return (0); // gestion basique, optionnel : erreur malloc
	while (len--)
	{
		buff[i++] = "0123456789"[num % BASE];
		num /= BASE;
	}
	while (i-- > 0)
		count += sn_print_buffer(buff[i], buf);
	free(buff);
	return (count);
}

static int	print_unsigned(unsigned num, t_flags *f, int len, t_buffer *buf)
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
		count = sn_print_width_buf(f, len, buf);
	count += print_unsigned_digits(num, f, len, buf);
	if (f->left_adjusted)
		count += sn_print_width_buf(f, len, buf);
	return (count);
}

int	sn_handle_unsigned(unsigned int u, t_flags *f, t_buffer *buf)
{
	int	count;
	int	numlen;

	numlen = sn_get_num_len(u, BASE);
	count = print_unsigned(u, f, numlen, buf);
	return (count);
}
