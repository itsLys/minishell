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

#include "ft_dprintf_utils.h"

static int	handle_fmt(int fd, const char *fmt, va_list args)
{
	t_flags	f;
	int		count;

	count = 0;
	while (*fmt)
	{
		if (*fmt != '%')
			count += print(f.fd, *(fmt++));
		else if (check_valid(++fmt))
		{
			parse_fmt(fd, fmt, args, &f);
			fmt += f.total;
			if (f.printed == -1)
				return (-1);
			count += f.printed;
		}
		else
			count += print(f.fd, '%');
	}
	if (catch_err(0) == -1)
		return (-1);
	return (count);
}

int	ft_dprintf(int fd, const char *fmt, ...)
{
	int		count;
	va_list	args;

	va_start(args, fmt);
	if (!fmt)
		return (-1);
	count = handle_fmt(fd, fmt, args);
	va_end(args);
	return (count);
}
