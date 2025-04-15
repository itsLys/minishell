/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 11:32:09 by ihajji            #+#    #+#             */
/*   Updated: 2024/11/09 11:32:09 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	prelen;
	size_t	suflen;
	size_t	total_size;
	char	*str;

	if (!s1 && !s2)
		return (ft_strdup(""));
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	prelen = ft_strlen(s1);
	suflen = ft_strlen(s2);
	total_size = prelen + suflen + 1;
	str = ft_calloc(total_size, 1);
	if (str == NULL)
		return (NULL);
	ft_strlcat(str, s1, total_size);
	ft_strlcat(str, s2, total_size);
	return (str);
}
