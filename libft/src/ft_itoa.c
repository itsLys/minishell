/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 11:32:09 by ihajji            #+#    #+#             */
/*   Updated: 2024/11/09 11:32:09 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	count_digits(long n)
{
	unsigned int	digits;

	digits = 1;
	while (n > 9)
	{
		n /= 10;
		digits++;
	}
	return (digits);
}

static int	resolve_sign(int n, long *num)
{
	if (n < 0)
	{
		*num = -(long)n;
		return (-1);
	}
	*num = n;
	return (1);
}

static void	write_num(char *str, long num, unsigned int chars)
{
	int	i;

	i = chars;
	str[i--] = '\0';
	while (i >= 0)
	{
		str[i--] = (num % 10) + '0';
		num /= 10;
	}
}

char	*ft_itoa(int n)
{
	long			num;
	unsigned int	chars;
	char			*str;
	int				sign;

	sign = resolve_sign(n, &num);
	chars = count_digits(num);
	str = ft_calloc(chars + (sign < 0) + 1, 1);
	if (str == NULL)
		return (NULL);
	if (sign < 0)
	{
		chars++;
		write_num(str, num, chars);
		str[0] = '-';
	}
	else
		write_num(str, num, chars);
	return (str);
}
