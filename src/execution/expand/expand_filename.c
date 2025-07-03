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

	mask = build_mask(filename);
	expand_var(filename, env, &mask);
	str_destroy(&mask);
	if (str_find(filename, " ") != -1 && str_find(filename, "\n") != -1
		&& str_find(filename, "\t") != -1)
		return (filename->data);
	return (NULL);

}
