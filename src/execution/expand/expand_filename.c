/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_filename.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 21:42:46 by zbengued          #+#    #+#             */
/*   Updated: 2025/07/15 19:19:15 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <execution.h>
#include <parsing.h>

bool	is_ambigusous(t_str *filename, t_str *mask)
{
	size_t	i;

	i = 0;
	while (i < filename->size)
	{
		if ((str_char_at(filename, i) == '\t'
				|| str_char_at(filename, i) == '\n'
				|| str_char_at(filename, i) == ' ')
			&& (str_char_at(mask, i) == 'N'))
			return (true);
		i++;
	}
	return (false);
}

char	*expand_filename(t_str *filename, t_env *env)
{
	t_str	mask;

	mask = build_mask(filename);
	expand_var(filename, env, &mask);
	str_peek_reset(filename);
	if (!str_peek(filename) || is_ambigusous(filename, &mask))
		return (remove_quotes(filename, &mask), str_destroy(&mask), NULL);
	expand_wildcard_in_str(filename, &mask);
	if (is_ambigusous(filename, &mask))
		return (remove_quotes(filename, &mask), str_destroy(&mask), NULL);
	remove_quotes(filename, &mask);
	return (str_destroy(&mask), filename->data);
}
