/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_inlut.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 23:33:37 by zbengued          #+#    #+#             */
/*   Updated: 2025/06/24 05:09:20 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <execution.h>

static void	skip_blank(t_str *input, t_str *mask)
{
	while (ft_isblank(str_peek(input))
		&& mask->data[input->peek] == 'N')
		str_peek_advance(input);
}

static void	push_segment(t_str_arr *result, t_str *input, size_t start,
		size_t end)
{
	t_str	tmp;

	tmp = str_substr(input, start, end - start);
	str_arr_push(result, tmp.data);
	str_destroy(&tmp);
}

static void	skip_and_update_start(t_str *input, t_str *mask, size_t *start)
{
	skip_blank(input, mask);
	*start = input->peek;
}

t_str_arr	split_input(t_str *input, t_str *mask)
{
	t_str_arr	result;
	size_t		start;

	str_arr_init(&result);
	str_peek_reset(input);
	str_peek_reset(mask);
	start = 0;
	while (str_peek(input))
	{
		if (ft_isblank(str_peek(input)) && mask->data[input->peek] == 'N')
		{
			if (input->peek > start)
				push_segment(&result, input, start, input->peek);
			skip_and_update_start(input, mask, &start);
		}
		else
			str_peek_advance(input);
	}
	if (input->peek > start)
		push_segment(&result, input, start, input->peek);
	return (result);
}
