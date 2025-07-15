/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_seg1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 21:57:11 by ihajji            #+#    #+#             */
/*   Updated: 2025/07/15 21:59:14 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

void	str_segment_remove(t_str *string, size_t start, size_t length)
{
	if (!string || start >= string->size)
		return ;
	if (start + length > string->size)
		length = string->size - start;
	ft_memmove(string->data + start, string->data + start + length, string->size
		- (start + length) + 1);
	string->size -= length;
}

char	*str_segment_extract(t_str *str, size_t start, size_t length)
{
	char	*result;

	if (!str || start >= str->size)
		return (NULL);
	if (start + length > str->size)
		length = str->size - start;
	result = ft_calloc(length + 1, sizeof(char));
	if (!result)
		return (NULL);
	ft_memcpy(result, str->data + start, length);
	result[length] = '\0';
	return (result);
}

char	*str_segment_slice(t_str *str, size_t start, size_t length)
{
	return (str_segment_extract(str, start, length));
}

void	str_segment_replace(t_str *str,
			size_t start,
			size_t length,
			char *new_text)
{
	if (!str || !new_text)
		return ;
	str_segment_remove(str, start, length);
	str_insert(str, start, new_text);
}
