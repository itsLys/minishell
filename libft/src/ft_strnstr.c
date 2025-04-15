/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 11:32:09 by ihajji            #+#    #+#             */
/*   Updated: 2024/11/09 11:32:09 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	nlen;

	nlen = ft_strlen(needle);
	if (ft_strlen(haystack) < nlen || len < nlen)
		return (NULL);
	i = 0;
	if (needle[0])
	{
		while (haystack[i] && i < len)
		{
			if (haystack[i] == needle[0])
			{
				j = 0;
				while (i + j < len && needle[j] && needle[j] == haystack[i + j])
					j++;
				if (needle[j] == '\0')
					return ((char *)(haystack + i));
			}
			i++;
		}
		return (NULL);
	}
	return ((char *)(haystack));
}
