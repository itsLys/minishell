/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 23:46:26 by zbengued          #+#    #+#             */
/*   Updated: 2025/06/24 05:41:06 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <execution.h>

void	remove_quote(t_str *input, t_str *mask)
{
	str_peek_reset(input);
	str_peek_reset(mask);
	while (str_peek(input))
	{
		if (str_peek(mask) == 'Q')
		{
			str_erase(mask, mask->peek, 1);
			str_erase(input, mask->peek, 1);
			continue ;
		}
		str_peek_advance(input);
		str_peek_advance(mask);
	}
}

static bool	process_arg(t_str_arr *args, t_env *env,
		t_str_arr *out, t_str_arr *masks)
{
	t_str_arr	split;
	t_str		mask;

	mask = build_mask(str_arr_peek(args));
	if (!mask.data)
		return (false);
	expand_var(str_arr_peek(args), env, &mask);
	remove_quote(str_arr_peek(args), &mask);
	split = split_input(str_arr_peek(args), &mask);
	str_arr_extend(out, &split);
	str_arr_destroy(&split);
	str_arr_push(masks, mask.data);
	// str_destroy(str_arr_peek(args));
	return (true);
}

char	**extract_args(t_str_arr *args, t_env *env_list)
{
	t_str_arr	new_args;
	t_str_arr	new_masks;

	str_arr_init(&new_args);
	str_arr_init(&new_masks);
	str_arr_peek_reset(args);
	while (args->peek < args->size)
	{
		if (!process_arg(args, env_list, &new_args, &new_masks))
		{
			str_arr_destroy(&new_args);
			str_arr_destroy(&new_masks);
			return (convert_str_arr(&new_args));
		}
		str_arr_peek_advance(args);
	}
	expand_all_wildcards(&new_args, &new_masks);
	str_arr_destroy(&new_masks);
	printf("%zu\n", new_args.size);
	return (convert_str_arr(&new_args));
}
