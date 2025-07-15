/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   123arr_string2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:56:47 by zbengued          #+#    #+#             */
/*   Updated: 2025/07/15 20:17:28 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_string.h>

t_str	*str_arr_peek(t_str_arr *arr)
{
	if (arr->peek >= arr->size)
		return (NULL);
	return (&arr->items[arr->peek]);
}

t_str	*str_arr_peek_advance(t_str_arr *arr)
{
	if (arr->peek >= arr->size)
		return (NULL);
	return (&arr->items[arr->peek++]);
}

void	str_arr_peek_reset(t_str_arr *arr)
{
	arr->peek = 0;
}

void	print_str_arr(t_str_arr *arr)
{
	size_t	i;

	i = 0;
	while (i < arr->size)
		printf("[%s] ", arr->items[i++].data);
	printf("\n");
}
