/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr_string4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 11:41:44 by zbengued          #+#    #+#             */
/*   Updated: 2025/06/24 11:42:32 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_string.h>

char	*convert_str(t_str *str)
{
	return (ft_strdup(str->data));
}

char	**convert_str_arr(t_str_arr *arr)
{
	size_t	i;
	char	**vec;

	vec = ft_calloc(arr->size + 1, sizeof(char *));
	i = 0;
	while (i < arr->size)
	{
		vec[i] = convert_str(arr->items + i);
		if (vec[i] == NULL)
			return ((char **) ft_free_vector(vec));
		i++;
	}
	return (vec);
}

t_str_arr	convert_vec_strarr(char **og)
{
	t_str_arr	arr;
	size_t		i;

	arr.size = 0;
	while (og[arr.size])
		arr.size++;

	arr.items = ft_calloc(arr.size, sizeof(t_str));
	if (!arr.items)
	{
		arr.size = 0;
		return (arr);
	}

	i = 0;
	while (i < arr.size)
	{
		arr.items[i] = str_new(og[i]);
		i++;
	}
	return (arr);
}
