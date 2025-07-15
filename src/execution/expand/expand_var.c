/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 23:34:55 by zbengued          #+#    #+#             */
/*   Updated: 2025/07/15 19:05:12 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <execution.h>

t_str	extreact_variable(t_str *input)
{
	size_t	i;
	t_str	variable_name;

	str_create(&variable_name, "");
	i = input->peek + 1;
	if (str_char_at(input, i) == '\'' || str_char_at(input, i) == '\"')
		return (variable_name);
	while (str_char_at(input, i) && is_valid_var_char(str_char_at(input, i)))
	{
		str_append_char(&variable_name, str_char_at(input, i));
		i++;
	}
	return (variable_name);
}

void	expand_mask(t_str *mask, t_str *name, t_str *val)
{
	t_str	new;

	if (val->size == 0)
	{
		str_erase(mask, mask->peek, name->size + 1);
		return ;
	}
	str_create(&new, "");
	str_append_char(&new, str_peek(mask));
	str_repeat(&new, val->size);
	str_erase(mask, mask->peek, name->size + 1);
	str_insert(mask, mask->peek, new.data);
	str_destroy(&new);
}

void	expand(t_str *input, t_str *mask, t_env *env)
{
	t_str	variable;
	t_str	value;

	variable = extreact_variable(input);
	value = get_env_value(env, variable.data);
	str_prepend(&variable, "$");
	str_segment_replace(input, input->peek, variable.size + 1, value.data);
	expand_mask(mask, &variable, &value);
	input->peek += value.size;
	mask->peek += value.size;
	str_destroy(&variable);
	str_destroy(&value);
}

void	expand_var(t_str *input, t_env *env, t_str *mask)
{
	str_peek_reset(mask);
	str_peek_reset(input);
	while (str_peek(input))
	{
		if (can_expand(input, mask)
			&& is_valid_first_char(input->data[input->peek + 1]))
			expand(input, mask, env);
		else
		{
			str_peek_advance(mask);
			str_peek_advance(input);
		}
	}
}
