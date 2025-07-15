/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_convert2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 22:52:06 by ihajji            #+#    #+#             */
/*   Updated: 2025/07/15 22:53:52 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

t_str	str_from_cstr(const char *cstr)
{
	t_str	str;
	size_t	len;

	if (!cstr)
	{
		str.data = NULL;
		str.size = 0;
		str.capacity = 0;
		return (str);
	}
	len = ft_strlen(cstr);
	str.data = malloc(len + 1);
	if (!str.data)
	{
		str.size = 0;
		str.capacity = 0;
		return (str);
	}
	ft_memcpy(str.data, cstr, len);
	str.data[len] = '\0';
	str.size = len;
	str.capacity = len + 1;
	return (str);
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
