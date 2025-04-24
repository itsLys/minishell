/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamic_arr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:40:31 by zbengued          #+#    #+#             */
/*   Updated: 2025/04/22 18:39:12 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stddef.h>
#include "stdio.h"

void	darr_init(t_darr *arr)
{
	arr->size = 0;
	arr->capacity = 4;
	arr->items = ft_calloc(sizeof(void *), arr->capacity);
	if (!arr->items)
		return;
} 

void	darr_push(t_darr *arr, void *item)
{
	void	**new_items;
	size_t	i;

	i = 0;
	if (arr->capacity <= arr->size)
	{
		arr->capacity *= 2;
		new_items = ft_calloc(sizeof(void *), arr->capacity);
		// TODO : change it with memcpy
		// while (i < arr->size)
		// {
		// 	new_items[i] = arr->items[i];
		// 	i++;
		// }
		ft_memcpy(new_items, arr->items, sizeof(void *) * arr->size);
		free(arr->items);
		arr->items = new_items;
	}
	arr->items[arr->size++] = item;
}

void	darr_free_arr(t_darr *arr, void (*f)(void *))
{
	size_t	i;

	i = 0;
	while (i < arr->size)
		f(arr->items[i++]);
	free(arr->items);
	arr->items = NULL;
	arr->size = 0;
	arr->capacity = 0;
}

