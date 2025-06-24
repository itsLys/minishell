/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_name_value.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 23:39:57 by zbengued          #+#    #+#             */
/*   Updated: 2025/06/24 05:09:26 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <execution.h>

t_str	get_env_value(t_env *env, char *name)
{
	t_env	*node;
	t_str	value;

	node = env_find_var(env, name);
	if (!node || !node->value)
		str_create(&value, ft_strdup(""));
	else
		str_create(&value, ft_strdup(node->value));
	return (value);
}

t_str	get_var_name(t_str *input, t_str *mask, char save_flag)
{
	size_t	start;

	start = input->peek;
	while ((ft_isalnum(str_peek(input)) && str_peek(input))
		&& str_peek(mask) == save_flag)
	{
		str_peek_advance(input);
		str_peek_advance(mask);
	}
	return (str_substr(input, start, input->peek - start));
}
