/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_filename.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 21:42:46 by zbengued          #+#    #+#             */
/*   Updated: 2025/07/02 21:46:46 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <execution.h>

char	*expand_filename(t_str *filename, t_env *env)
{
	t_str	mask;
	size_t	i;

	i = 0;
	mask = build_mask(filename);
	expand_var(filename, env, &mask);
	str_peek_reset(filename);
	if (!str_peek(filename))
		return (NULL);
	if (str_find(filename, " ") == -1 && str_find(filename, "\n") == -1
		&& str_find(filename, "\t") == -1 )
		return (filename->data);
	while (i < filename->size)
	{
		if ((str_char_at(filename, i) == '\t'
			|| str_char_at(filename, i) == '\n'
			|| str_char_at(filename, i) == ' ')
			&& (str_char_at(&mask, i) == 'N'))
			return (str_destroy(&mask), NULL);
		i++;
	}
	return (filename->data);
}
