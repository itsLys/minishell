/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_arr_extra.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 19:23:37 by ihajji            #+#    #+#             */
/*   Updated: 2025/07/15 20:08:55 by ihajji           ###   ########.fr       */
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

void	str_arr_insert(t_str_arr *arr, size_t index, char *text)
{
	t_str	new_str;
	size_t	i;

	if (index > arr->size)
		return ;
	if (!str_arr_resize_if_needed(arr))
		return ;
	i = arr->size;
	while (i > index)
	{
		arr->items[i] = arr->items[i - 1];
		i--;
	}
	str_create(&new_str, text);
	arr->items[index] = new_str;
	arr->size++;
}

void	str_arr_remove(t_str_arr *arr, size_t index)
{
	size_t	i;

	if (index >= arr->size)
		return ;
	str_destroy(&arr->items[index]);
	i = index;
	while (i + 1 < arr->size)
	{
		arr->items[i] = arr->items[i + 1];
		i++;
	}
	arr->size--;
}
