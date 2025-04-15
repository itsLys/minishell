/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 18:01:40 by ihajji            #+#    #+#             */
/*   Updated: 2025/02/17 22:52:27 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_atof(char *str)
{
	double	f;
	int		exp;
	int		sign;

	sign = 1;
	exp = 10;
	f = 0;
	while (*str == ' ')
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (ft_isdigit(*str))
		f = f * 10 + (*(str++) - '0');
	if (*str == '.')
		str++;
	while (ft_isdigit(*str))
	{
		f = f + (double)(*str++ - '0') / exp;
		exp *= 10;
	}
	return (f * sign);
}
