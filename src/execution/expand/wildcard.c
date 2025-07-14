/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 05:02:49 by zbengued          #+#    #+#             */
/*   Updated: 2025/07/14 22:56:55 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <execution.h>

bool	contains_wildcard_masked(t_str str, t_str mask)
{
	if (!str.data || !mask.data)
		return (false);
	str_peek_reset(&str);
	str_peek_reset(&mask);
	while (str_peek(&str) && str_peek(&mask))
	{
		if (str_peek(&str) == '*' && str_peek(&mask) == 'N')
			return (true);
		str_peek_advance(&str);
		str_peek_advance(&mask);
	}
	return (false);
}

static bool	match_after_star(t_str *pattern, t_str *mask, const char *str, size_t p_index)
{
	while (*str)
	{
		if (match_wildcard_from(pattern, mask, str, p_index))
			return (true);
		str++;
	}
	return (match_wildcard_from(pattern, mask, str, p_index));
}

bool	match_wildcard_from(t_str *pattern, t_str *mask, const char *str, size_t p_index)
{
	size_t	i;

	i = p_index;
	if (!pattern || !str || !mask)
		return (false);
	while (pattern->data[i])
	{
		if (pattern->data[i] == '*' && mask->data[i] == 'N')
		{
			while (pattern->data[i] == '*' && mask->data[i] == 'N')
				i++;
			if (!pattern->data[i])
				return (true);
			return (match_after_star(pattern, mask, str, i));
		}
		if (*str == '\0' || pattern->data[i] != *str)
			return (false);
		i++;
		str++;
	}
	return (*str == '\0');
}

bool	match_wildcard(t_str *pattern, t_str *mask, const char *str)
{
	return (match_wildcard_from(pattern, mask, str, 0));
}

void	expand_wildcard_in_str(t_str *input, t_str *mask)
{
	t_str			result;
	DIR				*dir;
	struct dirent	*entry;
	bool			found;

	if (!contains_wildcard_masked(*input, *mask))
		return ;
	found = false;
	result = str_new("");
	dir = opendir(".");
	if (!dir)
		return ;
	entry = readdir(dir);
	while (entry)
	{
		if (entry->d_name[0] == '.' && input->data[0] != '.')
		{
			entry = readdir(dir);
			continue;
		}
		if (match_wildcard_from(input, mask, entry->d_name, 0))
		{
			if (found)
				str_append_char(&result, ' ');
			str_append(&result, entry->d_name);
			found = true;
		}
		entry = readdir(dir);
	}
	closedir(dir);
	if (!found)
	{
		str_destroy(&result);
		return ;
	}
	str_destroy(input);
	*input = str_substr(&result, 0, result.size);
}

void	expand_all_wildcards(t_str_arr *args, t_str_arr *masks)
{
	size_t	i;
	size_t	limit;

	i = 0;
	limit = args->size;
	// printf("%zu = limit\n", limit);
	while (i < limit)
	{
		// printf("size masks = %zu\n", masks->size);
		// printf("size args = %zu\n", args->size);
		if (contains_wildcard_masked(args->items[i], masks->items[i]))
			expand_wildcard_at(args, masks, i++);
		else
			i++;
	}
}
