/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 23:46:08 by zbengued          #+#    #+#             */
/*   Updated: 2025/07/07 23:46:09 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_snprintf_utils.h"

void	sn_parse_flags(const char *fmt, t_flags *f)
{
	if (*fmt == '#')
		f->alt_form = 1;
	else if (*fmt == '0')
	{
		if (!f->left_adjusted)
			f->zero_padded = 1;
	}
	else if (*fmt == '-')
	{
		f->left_adjusted = 1;
		f->zero_padded = 0;
	}
	else if (*fmt == ' ')
		f->space_flag = 1;
	else if (*fmt == '+')
	{
		f->space_flag = 0;
		f->force_sign = 1;
	}
}

int	sn_parse_integer(const char *fmt, int *n, t_flags *f)
{
	int	count;

	count = 0;
	*n = ft_atoi(fmt);
	while (*fmt && ft_isdigit(*fmt))
	{
		count++;
		fmt++;
		f->total++;
	}
	return (count);
}

void	sn_print_conversion(char c, va_list args, t_flags *f, t_buffer *buf)
{
	if (c == 'c')
	{
		f->zero_padded = 0;
		f->printed += sn_handle_char(f, va_arg(args, int), buf);
	}
	else if (c == 's')
	{
		f->zero_padded = 0;
		f->printed += sn_handle_str(va_arg(args, char *), f, buf);
	}
	else if (c == 'p')
		f->printed += sn_handle_ptr(va_arg(args, unsigned long long), f, buf);
	else if (c == 'd' || c == 'i')
		f->printed += sn_handle_nbr(va_arg(args, int), f, buf);
	else if (c == 'u')
		f->printed += sn_handle_unsigned(va_arg(args, unsigned int), f, buf);
	else if (c == 'x' || c == 'X')
		f->printed += sn_handle_hex(va_arg(args, unsigned int), f, c, buf);
	else if (c == '%')
		f->printed += sn_print_buffer('%', buf);
	else if (c == '\0')
		f->printed = -1;
}

void	sn_parse_fmt(const char *fmt, va_list args, t_flags *f, t_buffer *buf)
{
	ft_memset(f, 0, sizeof(*f));
	while (*fmt && ft_strchr(FLAGS, *fmt))
	{
		sn_parse_flags(fmt++, f);
		f->total++;
	}
	if (ft_isdigit(*fmt))
		fmt += sn_parse_integer(fmt, &(f->width), f);
	if (*fmt == '.')
	{
		fmt++;
		f->total++;
		f->precision_flag = 1;
		fmt += sn_parse_integer(fmt, &(f->precision_value), f);
	}
	f->coversion = *fmt;
	f->total++;
	sn_print_conversion(*fmt, args, f, buf);
}
