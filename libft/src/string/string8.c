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
