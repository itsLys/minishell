/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string8.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:00:31 by zbengued          #+#    #+#             */
/*   Updated: 2025/06/26 15:43:16 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_string.h>

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

char	str_char_at(t_str *str, size_t i)
{
	if (!str || i >= str->size)
		return ('\0');
	return (str->data[i]);
}

void	str_append_char(t_str *str, char c)
{
	char	tmp[2];

	tmp[0] = c;
	tmp[1] = '\0';
	str_append(str, tmp);
}
