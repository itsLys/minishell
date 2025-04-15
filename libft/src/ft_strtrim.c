/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 11:32:09 by ihajji            #+#    #+#             */
/*   Updated: 2024/11/09 11:32:10 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	issep(char c, char const *set)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

static size_t	get_end(char const *s1, char const *set)
{
	size_t	i;

	i = ft_strlen(s1);
	while (i-- > 0)
	{
		if (!issep(s1[i], set))
			return (i);
	}
	return (i);
}

static size_t	get_start(char const *s1, char const *set)
{
	size_t	i;

	i = 0;
	while (s1[i] && issep(s1[i], set))
		i++;
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	s;
	size_t	e;

	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	s = get_start(s1, set);
	e = get_end(s1, set);
	str = ft_substr(s1, s, e - s + 1);
	if (!str)
		return (NULL);
	return (str);
}
