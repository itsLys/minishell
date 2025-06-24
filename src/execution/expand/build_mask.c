/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_mask.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 23:32:03 by zbengued          #+#    #+#             */
/*   Updated: 2025/06/24 05:10:05 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <execution.h>

static void	set_mask_as(t_str *mask, t_str *input, char *quote, char peek)
{
	*quote = peek;
	str_insert(mask, input->peek, "Q");
	str_peek_advance(input);
}

static void	choose_mask(t_str *mask, t_str *input, char quote)
{
	if (quote == '"')
		str_insert(mask, input->peek, "D");
	else if (quote == '\'')
		str_insert(mask, input->peek, "S");
	else
		str_insert(mask, input->peek, "N");
}

t_str	build_mask(t_str *input)
{
	t_str	mask;
	char	quote;

	str_init(&mask);
	quote = 0;
	while (str_peek(input))
	{
		if ((str_peek(input) == '"' || str_peek(input) == '\'') && !quote)
		{
			set_mask_as(&mask, input, &quote, str_peek(input));
			continue ;
		}
		else if (str_peek(input) == quote)
		{
			set_mask_as(&mask, input, &quote, 0);
			continue ;
		}
		choose_mask(&mask, input, quote);
		str_peek_advance(input);
	}
	return (mask);
}
