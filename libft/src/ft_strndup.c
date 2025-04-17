/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 22:49:32 by zbengued          #+#    #+#             */
/*   Updated: 2025/04/14 22:49:58 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_strndup(const char *src, size_t n)
{
	char *dest = malloc(n + 1);
	if (!dest)
		return NULL;
	ft_memcpy(dest, src, n);
	dest[n] = '\0';
	return dest;
}
