/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 20:23:48 by ihajji            #+#    #+#             */
/*   Updated: 2025/07/15 20:25:43 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

size_t	str_total_size(t_str *arr, size_t len, size_t delim_len)
{
	size_t	total;
	size_t	i;

	total = 0;
	i = 0;
	while (i < len)
	{
		total += arr[i].size;
		if (i < len - 1)
			total += delim_len;
		i++;
	}
	return (total);
}

void	str_fill(t_str *result, t_str *arr, size_t len, char *d)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		str_append(result, arr[i].data);
		if (i < len - 1 && d)
			str_append(result, d);
		i++;
	}
}
