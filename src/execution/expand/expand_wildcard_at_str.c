/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wild_card_at_str.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 19:06:12 by zbengued          #+#    #+#             */
/*   Updated: 2025/07/15 19:06:24 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parsing.h>
#include <execution.h>

static void	append_match_if_valid(t_str *result, bool *found, char *name)
{
	if (*found)
		str_append_char(result, ' ');
	str_append(result, name);
	*found = true;
}

static void	expand_wildcard_loop(t_str *input, t_str *mask,
		t_str *result, bool *found)
{
	DIR				*dir;
	struct dirent	*entry;

	dir = opendir(".");
	if (!dir)
		return ;
	entry = readdir(dir);
	while (entry)
	{
		if (entry->d_name[0] == '.' && input->data[0] != '.')
		{
			entry = readdir(dir);
			continue ;
		}
		if (match_wildcard_from(input, mask, entry->d_name, 0))
			append_match_if_valid(result, found, entry->d_name);
		entry = readdir(dir);
	}
	closedir(dir);
}

void	expand_wildcard_in_str(t_str *input, t_str *mask)
{
	t_str	result;
	bool	found;

	if (!contains_wildcard_masked(*input, *mask))
		return ;
	found = false;
	result = str_new("");
	expand_wildcard_loop(input, mask, &result, &found);
	if (!found)
	{
		str_destroy(&result);
		return ;
	}
	str_destroy(input);
	*input = str_substr(&result, 0, result.size);
}
