/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 23:34:55 by zbengued          #+#    #+#             */
/*   Updated: 2025/06/24 05:43:32 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <execution.h>

bool	is_valid_first_char(char c)
{
	return (ft_isalpha((unsigned char)c) || c == '_' || c == '"' || c == '\''
			|| c == '?');
}

bool	is_valid_var_char(char c)
{
	return (ft_isalnum((unsigned char)c) || c == '_' || c == '?');
}

bool	is_shell_variable(t_str str)
{
	if (str_peek(&str) != '$')
		return false;
	return true;
}

bool	can_expand(t_str *input, t_str *mask)
{
	if (str_peek(input) == '$'
		&& (str_peek(mask) == 'N' || str_peek(mask) == 'D'))
		return (true);
	return (false);
}

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
	str_replace(input, variable.data, value.data, ONE);
	expand_mask(mask, &variable, &value);
	input->peek += *(size_t *)ternary((variable.size > value.size),
		&variable.size, &value.size);
	mask->peek += *(size_t *)ternary((variable.size > value.size),
		&variable.size, &value.size);
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
		printf("[%s][%s]\n", input->data, mask->data);
	}
// remove_quote_expand(input, mask);
}
