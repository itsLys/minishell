/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr_string3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 01:05:34 by zbengued          #+#    #+#             */
/*   Updated: 2025/06/24 01:06:52 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_string.h>

static int	str_arr_resize_if_needed(t_str_arr *arr)
{
	t_str	*tmp;
	size_t	i;

	if (arr->size < arr->capacity)
		return (1);
	tmp = ft_calloc(sizeof(t_str), arr->capacity * 2);
	if (!tmp)
		return (0);
	i = arr->size;
	while (i--)
		tmp[i] = arr->items[i];
	free(arr->items);
	arr->items = tmp;
	arr->capacity *= 2;
	return (1);
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

void	str_arr_free(t_str_arr *arr)
{
	size_t	i;

	i = 0;
	while (i < arr->size)
	{
		str_destroy(&arr->items[i]);
		i++;
	}
	free(arr->items);
	arr->items = NULL;
	arr->size = 0;
	arr->capacity = 0;
	arr->peek = 0;
}
