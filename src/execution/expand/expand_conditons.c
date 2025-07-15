/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_conditons.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 18:04:47 by zbengued          #+#    #+#             */
/*   Updated: 2025/07/15 19:09:46 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parsing.h>
#include <execution.h>

bool	is_valid_first_char(char c)
{
	return (ft_isalpha((unsigned char)c) || c == '_'
		|| c == '?');
}

bool	is_valid_var_char(char c)
{
	return (ft_isalnum((unsigned char)c) || c == '_' || c == '?');
}

bool	is_shell_variable(t_str str)
{
	if (str_peek(&str) != '$')
		return (false);
	return (true);
}

bool	can_expand(t_str *input, t_str *mask)
{
	if (str_peek(input) == '$'
		&& (str_peek(mask) == 'N' || str_peek(mask) == 'D'))
		return (true);
	return (false);
}
