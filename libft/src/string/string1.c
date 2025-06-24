/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 18:34:27 by zbengued          #+#    #+#             */
/*   Updated: 2025/06/19 18:50:17 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_string.h>

void	str_init(t_str *str)
{
	str->data = ft_calloc(INIT_CAPACITY + 1, sizeof(char));
	if (!str->data)
		return ;
	str->size = 0;
	str->capacity = INIT_CAPACITY;
	str->peek = 0;
}

void	str_destroy(t_str *str)
{
	if (str->data)
		free(str->data);
	str->data = NULL;
	str->size = 0;
	str->capacity = 0;
	str->peek = 0;
}

void	str_ensure_capacity(t_str *str, size_t needed_capacity)
{
	size_t	new_capacity;
	char	*new_data;

	if (str->capacity >= needed_capacity)
		return ;
	new_capacity = str->capacity;
	while (new_capacity < needed_capacity)
		new_capacity *= 2;
	new_data = ft_calloc(new_capacity + 1, sizeof(char));
	if (!new_data)
		return ;
	ft_memcpy(new_data, str->data, str->size);
	new_data[str->size] = '\0';
	free(str->data);
	str->data = new_data;
	str->capacity = new_capacity;
}

void	str_set(t_str *str, char *new_data)
{
	size_t	new_len;

	if (!str || !new_data)
		return ;
	new_len = ft_strlen(new_data);
	str_ensure_capacity(str, new_len);
	ft_memcpy(str->data, new_data, new_len);
	str->data[new_len] = '\0';
	str->size = new_len;
	str->peek = 0;
}

void	str_append(t_str *str, char *to_add)
{
	size_t	len;

	if (!str || !to_add)
		return ;
	len = ft_strlen(to_add);
	str_ensure_capacity(str, str->size + len);
	ft_memcpy(str->data + str->size, to_add, len);
	str->size += len;
	str->data[str->size] = '\0';
}
