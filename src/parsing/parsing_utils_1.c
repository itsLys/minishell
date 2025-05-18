/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 17:28:31 by zbengued          #+#    #+#             */
/*   Updated: 2025/05/18 17:32:37 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parsing.h>

bool	is_word(t_token_type val)
{
	return ((val == T_WORD));
}

bool	is_and_or(t_token_type type)
{
	return (type == T_OR || type == T_AND);
}

bool	is_redi(t_token_type val)
{
	return ((val <= T_HERDOC && val >= T_REDIRI));
}

bool	valid_pipe(t_token **tokens)
{
	return (is_word((*tokens)->t_type) || is_redi((*tokens)->t_type)
		|| ((*tokens)->t_type == T_LPAR));
}

bool	valid_compound(t_token **tokens)
{
	return ((*tokens)->t_type != T_OR && (*tokens)->t_type != T_AND
		&& (*tokens)->t_type != T_PIPE);
}
