/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:21:09 by ihajji            #+#    #+#             */
/*   Updated: 2024/11/30 09:36:50 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_width(t_flags *f, int n)
{
	int	count;

	count = 0;
	while (f->width - n > 0)
	{
		if (f->zero_padded)
			print('0');
		else
			print(' ');
		f->width--;
		count++;
	}
	return (count);
}

int	get_num_len(unsigned long long n, unsigned int base)
{
	int	len;

	len = 1;
	while (n > base - 1)
	{
		n /= base;
		len++;
	}
	return (len);
}

int	check_valid(const char *fmt)
{
	while (*fmt && ft_strchr(FLAGS, *fmt))
		fmt++;
	while (*fmt && ft_isdigit(*fmt))
		fmt++;
	if (*fmt == '.')
		fmt++;
	while (*fmt && ft_isdigit(*fmt))
		fmt++;
	if (ft_strchr(CONVERSIONS, *fmt))
		return (1);
	return (0);
}

int	catch_err(int n)
{
	static int	e;

	if (n == -1 && e == 0)
		e = -1;
	return (e);
}

int	print(char c)
{
	if (catch_err(ft_putchar_fd(c, 1)) == -1)
		return (-1);
	return (1);
}
