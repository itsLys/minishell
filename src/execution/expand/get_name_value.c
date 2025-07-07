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
	char	*tmp;

	if (!ft_strcmp(name, "?"))
	{
		tmp = ft_itoa(g_interrupted[2]);
		str_create(&value, tmp);
		free(tmp);
		return (value);
	}
	node = env_find_var(env, name);
	if (!node || !node->value)
		str_create(&value, "");
	else
		str_create(&value, node->value);
	return (value);
}

t_str	get_varname(t_str *input)
{
	t_str	var;
	char	c;

	str_create(&var, "");
	if (str_peek(input) != '$')
		return var;
	str_peek_advance(input);
	c = str_peek(input);
	if (c == '\0' || c == '\'' || c == '\"')
		return var;
	if (!is_valid_first_char(c))
		return var;
	str_append_char(&var, c);
	str_peek_advance(input);
	while (str_peek(input))
	{
		if (!is_valid_var_char(str_peek(input)))
			break;
		str_append_char(&var, str_peek(input));
		str_peek_advance(input);
	}
	return var;
}
