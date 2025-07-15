/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_convert1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 22:16:19 by ihajji            #+#    #+#             */
/*   Updated: 2025/07/15 22:51:59 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

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
			return ((char **)ft_free_vector(vec));
		i++;
	}
	return (vec);
}

char	*str_to_cstr(t_str *str)
{
	char	*copy;

	if (!str || !str->data)
		return (NULL);
	copy = malloc(str->size + 1);
	if (!copy)
		return (NULL);
	ft_memcpy(copy, str->data, str->size);
	copy[str->size] = '\0';
	return (copy);
}

