/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 23:46:26 by zbengued          #+#    #+#             */
/*   Updated: 2025/07/15 19:04:57 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <execution.h>

void	remove_quotes(t_str *str, t_str *mask)
{
	str_peek_reset(str);
	str_peek_reset(mask);
	while (str_peek(str))
	{
		if (str_peek(mask) == 'Q')
		{
			str_erase(str, str->peek, 1);
			str_erase(mask, str->peek, 1);
			continue ;
		}
		str_peek_advance(str);
		str_peek_advance(mask);
	}
}

void	remove_quote(t_str *str)
{
	char	current_quote;
	char	c;

	current_quote = 0;
	str_peek_reset(str);
	while (str->peek < str->size)
	{
		c = str_peek(str);
		if ((c == '\'' || c == '"'))
		{
			if (current_quote == 0)
			{
				current_quote = c;
				str_erase(str, str->peek, 1);
				continue ;
			}
			else if (current_quote == c)
			{
				current_quote = 0;
				str_erase(str, str->peek, 1);
				continue ;
			}
		}
		str_peek_advance(str);
	}
}

bool	is_assign(t_str_arr *args)
{
	const char	*ptr;

	if (!(args->size > args->peek
			&& !ft_strcmp(args->items[0].data, "export")
			&& args->size > 1))
		return (false);
	if (args->size == 1)
		return (false);
	ptr = args->items[args->peek].data;
	while (*ptr && *ptr != '=')
	{
		if (*ptr == '$')
			return (false);
		ptr++;
	}
	if (*ptr == '\0')
		return (false);
	return (true);
}

static bool	process_arg(t_str_arr *args, t_env *env,
		t_str_arr *out, t_str_arr *masks)
{
	t_str_arr	splited_input;
	t_str_arr	splited_mask;
	t_str		mask;

	mask = build_mask(str_arr_peek(args));
	if (!mask.data)
		return (false);
	expand_var(str_arr_peek(args), env, &mask);
	if (str_arr_peek(args)->data[0] == '\0')
		return (str_destroy(&mask), true);
	remove_quotes(str_arr_peek(args), &mask);
	if (is_assign(args) == true)
	{
		str_arr_init(&splited_input);
		str_arr_push(&splited_input, args->items[args->peek].data);
	}
	else
		splited_input = split_input(str_arr_peek(args), &mask);
	splited_mask = str_arr_split(&mask, ' ');
	str_arr_extend(out, &splited_input);
	str_arr_extend(masks, &splited_mask);
	str_arr_destroy(&splited_input);
	str_arr_destroy(&splited_mask);
	str_destroy(&mask);
	return (true);
}

char	**extract_args(t_str_arr *args, t_env *env_list)
{
	t_str_arr	new_args;
	t_str_arr	new_masks;
	char		**argv;

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
	argv = convert_str_arr(&new_args);
	str_arr_destroy(&new_args);
	return (argv);
}
