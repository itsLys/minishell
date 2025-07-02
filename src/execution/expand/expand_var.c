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
	return (ft_isalpha((unsigned char)c) || c == '_');
}

bool	is_valid_var_char(char c)
{
	return (ft_isalnum((unsigned char)c) || c == '_');
}

bool	is_shell_variable(t_str str)
{
	if (str_peek_advance(&str) != '$')
		return false;
	else if (str_peek(&str))
		return true;
	return false;
}

static bool	is_expandable(t_str mask, t_str input)
{
	return (str_peek(&input) == '$'
		&& (str_peek(&mask) == 'N' || str_peek(&mask) == 'D'));
}

static bool	can_expand(t_str input, t_str mask)
{
	return (is_shell_variable(input) && is_expandable(mask, input));
}

void	expand_mask(t_str *mask, t_str *name, t_str *val)
{
	t_str	new;
	str_create(&new, "");
	str_append_char(&new, str_peek(mask));
	str_repeat(&new, val->size);
}

void	expand(t_str *input, t_str *mask, t_env *env)
{
	t_str	var_name;
	t_str	var_value;
	size_t	value_len;
	size_t	name_len;

	var_name = get_varname(input);
	var_value = get_env_value(env, var_name.data);
	str_prepend(&var_name, "$");
	name_len = ft_strlen(var_name.data) - 1;
	if (ft_strlen(var_value.data) == 0)
		value_len = 0;
	else
		value_len = ft_strlen(var_value.data) - 1;
	// printf(" varname : [%s], value : [%s], mask : [%s]\n the peek = %zu\n", var_name.data, var_value.data, mask->data,input->peek);
	str_replace(input, var_name.data, var_value.data, ONE);
	str_segment_set(mask, mask->peek - name_len, value_len, mask->peek);
	// printf("----------\n");
	// printf(" varname : [%s], value : [%s], mask : [%s]\n the peek = %zu\n", var_name.data, var_value.data, mask->data,input->peek);
	ternary_((t_ternary){(name_len > value_len), &name_len, &value_len,
		sizeof(size_t), &mask->peek});
	ternary_((t_ternary){(name_len > value_len), &name_len, &value_len,
		sizeof(size_t), &mask->peek});
}

void	expand_var(t_str *input, t_env *env, t_str *mask)
{
	str_peek_reset(mask);
	str_peek_reset(input);
	printf("the input : %s\n", input->data);
	while (str_peek(input))
	{
		printf("the peek = %c\n", str_peek(input));
		if (can_expand(*input, *mask))
			expand(input, mask, env);
		else
		{
			str_peek_advance(mask);
			str_peek_advance(input);
		}
	}
}
