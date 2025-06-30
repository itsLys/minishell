/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string9.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 17:33:29 by zbengued          #+#    #+#             */
/*   Updated: 2025/06/30 17:36:15 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_string.h>

void	str_replace_char(t_str *str, char old_char, char new_char)
{
	size_t	i;

	if (!str || !str->data)
		return ;
	i = 0;
	while (i < str->size)
	{
		if (str->data[i] == old_char)
			str->data[i] = new_char;
		i++;
	}
}
