/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 11:32:08 by ihajji            #+#    #+#             */
/*   Updated: 2024/11/09 11:32:08 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*mem;
	size_t	total;

	total = nmemb * size;
	if (nmemb && size && total / nmemb != size)
		return (NULL);
	mem = malloc(total);
	if (!mem)
		return (NULL);
	ft_memset(mem, 0, total);
	return (mem);
}
