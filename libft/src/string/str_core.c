/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_core.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 20:15:31 by ihajji            #+#    #+#             */
/*   Updated: 2025/07/15 20:17:28 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

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

void	str_create(t_str *str, char *text)
{
	str_init(str);
	str_set(str, text);
}

t_str	str_new(char *src)
{
	t_str	new;

	new.peek = 0;
	if (!src)
	{
		new.data = NULL;
		new.size = 0;
		new.capacity = 0;
		return (new);
	}
	new.size = ft_strlen(src);
	new.data = ft_strdup(src);
	new.capacity = new.size + 1;
	if (!new.data)
	{
		new.size = 0;
		new.capacity = 0;
	}
	return (new);
}
