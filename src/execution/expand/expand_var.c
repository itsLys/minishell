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

static bool	is_expandable(t_str mask, t_str input)
{
	if (str_peek(&input) == '$' && str_peek(&mask) == 'N'
		&& str_peek_advance(&mask) != str_peek(&mask))
		return (true);
	else if (str_peek(&input) == '$' && str_peek(&mask) != 'N'
		&& str_peek_advance(&mask) != str_peek(&mask))
		return (false);
	return (str_peek(&mask) == 'D' || str_peek(&mask) == 'N');
}

static bool	check_if_is_variable(t_str str)
{
	if (!str.data || !str_peek(&str))
		return (false);
	if (str_peek(&str) != '$')
		return (false);
	str_peek_advance(&str);
	if (!ft_isalpha(str_peek(&str)))
		return (false);
	str_peek_advance(&str);
	while (str_peek(&str))
	{
		if (!ft_isalnum(str_peek(&str)) && str_peek(&str) != '_')
			break ;
		str_peek_advance(&str);
	}
	return (true);
}

static bool	can_expand(t_str input, t_str mask)
{
	return (check_if_is_variable(input) && is_expandable(mask, input));
}

void	expand(t_str *input, t_str *mask, t_env *env)
{
	t_str	var_name;
	t_str	var_valu;
	size_t	valu_len;
	size_t	name_len;

	str_peek_advance(input);
	var_name = get_var_name(input, mask, str_peek(mask));
	var_valu = get_env_value(env, var_name.data);
	str_prepend(&var_name, "$");
	name_len = ft_strlen(var_name.data) - 1;
	valu_len = ft_strlen(var_valu.data) - 1;
	str_replace(input, var_name.data, var_valu.data, ONE);
	str_segment_set(mask, mask->peek - name_len , valu_len, mask->peek);
	ternary((t_ternary){(name_len >= valu_len), &name_len, &valu_len,
		sizeof(size_t), &mask->peek});
	ternary((t_ternary){(name_len >= valu_len), &name_len, &valu_len,
		sizeof(size_t), &mask->peek});
}

void	expand_var(t_str *input, t_env *env, t_str *mask)
{
	str_peek_reset(mask);
	str_peek_reset(input);
	while (str_peek(input))
	{
		if (can_expand(*input, *mask))
			expand(input, mask, env);
		else
		{
			str_peek_advance(mask);
			str_peek_advance(input);
		}
	}
}
