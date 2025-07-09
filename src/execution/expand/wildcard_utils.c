/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 00:41:47 by zbengued          #+#    #+#             */
/*   Updated: 2025/06/24 05:41:21 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <execution.h>
#include <parsing.h>

static void	collect_wildcard_matches(t_str_arr *matches, const char *pattern)
{
	DIR				*dir;
	struct dirent	*entry;

	dir = opendir(".");
	if (!dir)
		return ;
	entry = readdir(dir);
	while (entry)
	{
		if ((entry->d_name[0] == '.' && pattern[0] != '.'))
		{
			entry = readdir(dir);
			continue ;
		}
		if (match_wildcard(pattern, entry->d_name))
			str_arr_push(matches, entry->d_name);
		entry = readdir(dir);
	}
	closedir(dir);
}

static void	remove_arg_and_mask(t_str_arr *args, t_str_arr *masks, size_t index)
{
	str_destroy(&args->items[index]);
	str_destroy(&masks->items[index]);
	while (index + 1 < args->size)
	{
		args->items[index] = args->items[index + 1];
		masks->items[index] = masks->items[index + 1];
		index++;
	}
	args->size--;
	masks->size--;
}

static void	insert_matches(t_str_arr *args, t_str_arr *masks,
							t_str_arr *matches, size_t index)
{
	size_t	i;
	t_str	tmp_mask;

	i = 0;
	while (i < matches->size)
	{
		tmp_mask = str_new_fill(matches->items[i].size, 'N');
		str_arr_insert(args, index + i, matches->items[i].data);
		str_arr_insert(masks, index + i, tmp_mask.data);
		str_destroy(&tmp_mask);
		i++;
	}
}

void	expand_wildcard_at(t_str_arr *args, t_str_arr *masks, size_t index)
{
	t_str_arr	matches;

	str_arr_init(&matches);
	// printf("before ! \n");
	collect_wildcard_matches(&matches, args->items[index].data);
	// printf("after  ! \n");
	if (matches.size == 0)
	{
		str_arr_destroy(&matches);
		return ;
	}
	remove_arg_and_mask(args, masks, index);
	insert_matches(args, masks, &matches, index);
	str_arr_destroy(&matches);
}
