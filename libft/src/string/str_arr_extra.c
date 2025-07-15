/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_arr_extra.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 20:11:41 by ihajji            #+#    #+#             */
/*   Updated: 2025/07/15 20:15:20 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

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

t_str_arr	str_arr_split(t_str *str, char c)
{
	size_t		i;
	size_t		count;
	t_str		*split;
	t_str_arr	result;

	i = 0;
	count = 0;
	str_arr_init(&result);
	split = str_split(str, c, &count);
	while (i < count)
	{
		str_arr_push(&result, split[i].data);
		str_destroy(&split[i]);
		i++;
	}
	free(split);
	return (result);
}

char	**str_arr_to_cstr_array(t_str_arr *arr)
{
	char	**vec;
	size_t	i;

	if (!arr || !arr->size)
		return (NULL);
	vec = malloc(sizeof(char *) * (arr->size + 1));
	if (!vec)
		return (NULL);
	i = 0;
	while (i < arr->size)
	{
		vec[i] = ft_strdup(arr->items[i].data);
		i++;
	}
	vec[i] = NULL;
	return (vec);
}

void	print_str_arr(t_str_arr *arr)
{
	size_t	i;

	i = 0;
	while (i < arr->size)
		printf("[%s] ", arr->items[i++].data);
	printf("\n");
}

t_str_arr	str_arr_from_cstr_array(char **cstr)
{
	t_str_arr	arr;
	size_t		count;
	size_t		i;

	arr.items = NULL;
	arr.size = 0;
	arr.capacity = 0;
	arr.peek = 0;
	if (!cstr)
		return (arr);
	count = 0;
	while (cstr[count])
		count++;
	arr.items = malloc(sizeof(t_str) * count);
	if (!arr.items)
		return (arr);
	arr.capacity = count;
	arr.size = count;
	i = 0;
	while (i < count)
	{
		arr.items[i] = str_new(cstr[i]);
		i++;
	}
	return (arr);
}
