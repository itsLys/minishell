/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 23:46:59 by zbengued          #+#    #+#             */
/*   Updated: 2025/07/07 23:47:00 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_snprintf_utils.h"

static int	printnstr(t_flags *f, char *str, int len, t_buffer *buf)
{
	int	count;
	int	n;

	count = 0;
	n = len;
	if (!f->left_adjusted)
		count += sn_print_width_buf(f, len, buf);
	while (n-- && *str)
		count += sn_print_buffer(*(str++), buf);
	if (f->left_adjusted)
		count += sn_print_width_buf(f, len, buf);
	return (count);
}

static int	handle_str_precision(t_flags *f, char *str, t_buffer *buf)
{
	int	count;
	int	len;

	count = 0;
	len = ft_strlen(str);
	if (f->precision_flag && f->precision_value < len)
		len = f->precision_value;
	count += printnstr(f, str, len, buf);
	return (count);
}

static int	handle_null_str(t_flags *f, t_buffer *buf)
{
	int		count;
	char	*str;

	count = 0;
	str = "(null)";
	if (f->precision_flag && f->precision_value >= 0
		&& f->precision_value < (int)ft_strlen(str))
		count += sn_print_width_buf(f, 0, buf);
	else
		count += handle_str_precision(f, str, buf);
	return (count);
}

int	sn_handle_str(char *str, t_flags *f, t_buffer *buf)
{
	int	count;

	count = 0;
	if (!str)
		count += handle_null_str(f, buf);
	else
		count += handle_str_precision(f, str, buf);
	return (count);
}
