/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 11:31:59 by ihajji            #+#    #+#             */
/*   Updated: 2024/11/09 11:32:45 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(char c)
{
	if (c == ' ' || (c >= '\t' && c <= '\r'))
		return (1);
	return (0);
}

static const char	*skip_spaces(const char *nptr)
{
	while (*nptr && ft_isspace(*nptr))
		nptr++;
	return (nptr);
}

static const char	*resolve_sign(const char *nptr, int *sign)
{
	*sign = 1;
	if (*nptr && (*nptr == '-' || *nptr == '+'))
	{
		if (*nptr == '-')
			*sign = -(*sign);
		nptr++;
	}
	return (nptr);
}

int	ft_atoi(const char *nptr)
{
	long	n;
	long	prev;
	int		sign;

	n = 0;
	nptr = skip_spaces(nptr);
	nptr = resolve_sign(nptr, &sign);
	while (*nptr && ft_isdigit(*nptr))
	{
		prev = n;
		n = (*(nptr++) - '0') + n * 10;
		if (n < prev)
		{
			if (sign == -1)
				return (0);
			return (-1);
		}
	}
	return (n * sign);
}
