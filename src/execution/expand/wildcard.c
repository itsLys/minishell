/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 05:02:49 by zbengued          #+#    #+#             */
/*   Updated: 2025/06/24 05:28:07 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <execution.h>

bool	contains_wildcard_masked(t_str *str, t_str *mask)
{
	size_t	i;

	if (!str->data || !mask->data)
		return (false);
	i = 0;
	while (str->data[i])
	{
		if (str->data[i] == '*' && mask->data[i] == 'N')
			return (true);
		i++;
	}
	return (false);
}

static bool	match_after_star(const char *pattern, const char *str)
{
	while (*str)
	{
		if (match_wildcard(pattern, str))
			return (true);
		str++;
	}
	return (match_wildcard(pattern, str));
}

bool	match_wildcard(const char *pattern, const char *str)
{
	if (!pattern || !str)
		return (false);
	while (*pattern)
	{
		if (*pattern == '*')
		{
			while (*pattern == '*')
				pattern++;
			if (!*pattern)
				return (true);
			return (match_after_star(pattern, str));
		}
		if (*pattern != *str)
			return (false);
		pattern++;
		str++;
	}
	return (!(*str));
}

void	expand_all_wildcards(t_str_arr *args, t_str_arr *masks)
{
	size_t	i;

	i = 0;
	while (i < args->size)
	{
		if (contains_wildcard_masked(&args->items[i], &masks->items[i]))
			expand_wildcard_at(args, masks, i++);
		else
			i++;
	}
}
