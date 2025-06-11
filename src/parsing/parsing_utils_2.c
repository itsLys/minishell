/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 17:29:35 by zbengued          #+#    #+#             */
/*   Updated: 2025/05/18 18:02:24 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parsing.h>
#include <stdio.h>

bool	is_word_or_redir(t_token_type type)
{
	return (is_word(type) || is_redi(type));
}

bool	is_operator(t_token_type type)
{
	return (type < T_PIPE || type > T_AND);
}

size_t	counter(t_token	**tokens, bool mode)
{
	t_token	*act;
	size_t	i;

	i = 0;
	act = *tokens;
	while (mode == WORDS && act && is_word(act->t_type))
	{
		i++;
		act = act->next;
	}
	while (mode == REDIR && act && is_redi(act->t_type))
	{
		i++;
		act = act->next;
	}
	return (i);
}

void	consume_word(t_token **tokens, t_ast_node *args_node, size_t *i)
{
	char	*mask;

	mask = quote_mask((*tokens)->val);
	remove_quotes((*tokens)->val, mask);
	args_node->args[*i] = ft_strdup((*tokens)->val);
	args_node->mask[*i] = ft_strdup(mask);
	(*i)++;
	*tokens = (*tokens)->next;
}

void	consume_redir(t_token **tokens, t_ast_node *red_list)
{
	ast_add_child(red_list,
		ast_new((t_grammar)(*tokens)->t_type, (*tokens)->val));
	*tokens = (*tokens)->next;
}
