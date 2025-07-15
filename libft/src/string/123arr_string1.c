/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr_string1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 16:43:19 by zbengued          #+#    #+#             */
/*   Updated: 2025/06/24 01:08:46 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_string.h>

void	str_arr_init(t_str_arr *arr)
{
	arr->items = ft_calloc(sizeof(t_str), 4);
	if (!arr->items)
		return ;
	arr->size = 0;
	arr->capacity = 4;
}

void	str_arr_destroy(t_str_arr *arr)
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
}

void	str_arr_push(t_str_arr *arr, char *text)
{
	t_str	new_str;
	t_str	*tmp;
	size_t	i;

	i = 0;
	if (arr->size >= arr->capacity)
	{
		tmp = ft_calloc(sizeof(t_str), arr->capacity * 2);
		if (!tmp)
			return ;
		while (i < arr->size)
		{
			tmp[i] = arr->items[i];
			i++;
		}
		free(arr->items);
		arr->items = tmp;
		arr->capacity *= 2;
	}
	str_init(&new_str);
	str_set(&new_str, text);
	arr->items[arr->size++] = new_str;
}

void	str_arr_extend(t_str_arr *dest, t_str_arr *src)
{
	size_t	i;

	i = 0;
	while (i < src->size)
		str_arr_push(dest, src->items[i++].data);
}

t_str	*str_arr_get(t_str_arr *arr, size_t index)
{
	if (index >= arr->size)
		return (NULL);
	return (&arr->items[index]);
}
