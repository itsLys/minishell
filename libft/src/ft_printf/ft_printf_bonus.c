/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:42:31 by ihajji            #+#    #+#             */
/*   Updated: 2024/11/30 09:36:26 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	handle_fmt(const char *fmt, va_list args)
{
	t_flags	f;
	int		count;

	count = 0;
	while (*fmt)
	{
		if (*fmt != '%')
			count += print(*(fmt++));
		else if (check_valid(++fmt))
		{
			parse_fmt(fmt, args, &f);
			fmt += f.total;
			if (f.printed == -1)
				return (-1);
			count += f.printed;
		}
		else
			count += print('%');
	}
	if (catch_err(0) == -1)
		return (-1);
	return (count);
}

int	ft_printf(const char *fmt, ...)
{
	int		count;
	va_list	args;

	va_start(args, fmt);
	if (!fmt)
		return (-1);
	count = handle_fmt(fmt, args);
	va_end(args);
	return (count);
}
