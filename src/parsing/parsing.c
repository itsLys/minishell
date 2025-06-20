/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 16:27:18 by zbengued          #+#    #+#             */
/*   Updated: 2025/06/11 17:19:40 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stddef.h>
#include <stdio.h>

// WARN: SHOULD EXIT IN CASE OF CALLOC FAILING
t_ast_node	*simple_command(t_token **tokens)
{
	t_ast_node	*node[7];
	size_t		i;

	i = 0;
	node[I_SIMPLE_COMMAND] = ast_new(G_SIMPLE_COMMAND, NULL);
	node[I_RED_LIST] = ast_new(G_REDIRECT_LIST, NULL);
	node[I_ARGLIST] = ast_new(G_ARGS, NULL);
	node[I_ARGLIST]->args = ft_calloc(sizeof(char *), (counter(tokens, 0) + 1));
	node[I_ARGLIST]->mask = ft_calloc(sizeof(char *), (counter(tokens, 0) + 1));
	if (!node[I_ARGLIST]->args || !node[I_ARGLIST]->mask)
		return (NULL);
	while (*tokens && is_word_or_redir((*tokens)->t_type))
	{
		if (is_word((*tokens)->t_type))
			consume_word(tokens, node[I_ARGLIST], &i);
		else if (*tokens && is_redi((*tokens)->t_type))
			consume_redir(tokens, node[I_RED_LIST]);
		else if (!(*tokens) || !is_word_or_redir((*tokens)->t_type))
			break ;
	}
	if (*tokens && (*tokens)->t_type == T_LPAR)
		return (NULL);
	return (ast_add_child(node[I_SIMPLE_COMMAND], node[I_ARGLIST]),
		ast_add_child(node[I_SIMPLE_COMMAND], node[I_RED_LIST]),
		node[I_SIMPLE_COMMAND]);
}

t_ast_node	*subshell(t_token **tokens)
{
	t_ast_node	*node[7];

	node[I_RED_LIST] = ast_new(G_REDIRECT_LIST, NULL);
	node[I_SUBSHELL] = ast_new(G_SUBSHELL, NULL);
	*tokens = (*tokens)->next;
	if (!(*tokens) || (*tokens && (!is_word((*tokens)->t_type)
				&& !is_redi((*tokens)->t_type))))
		return (NULL);
	node[I_COMPOUND_COMMAND] = compound_command(tokens, true);
	if (!node[I_COMPOUND_COMMAND])
		return (NULL);
	if (!(*tokens))
		return (NULL);
	*tokens = (*tokens)->next;
	if (*tokens && is_word((*tokens)->t_type))
		return (NULL);
	while (*tokens && is_redi((*tokens)->t_type))
		consume_redir(tokens, node[I_RED_LIST]);
	ast_add_child(node[I_SUBSHELL], node[I_COMPOUND_COMMAND]);
	ast_add_child(node[I_SUBSHELL], node[I_RED_LIST]);
	return (node[I_SUBSHELL]);
}

t_ast_node	*command(t_token **tokens)
{
	t_ast_node	*node[7];

	node[I_COMMAND] = ast_new(G_COMMAND, NULL);
	if (is_word((*tokens)->t_type) || is_redi((*tokens)->t_type))
	{
		node[I_SIMPLE_COMMAND] = simple_command(tokens);
		if (!node[I_SIMPLE_COMMAND])
			return (NULL);
		ast_add_child(node[I_COMMAND], node[I_SIMPLE_COMMAND]);
		return (node[I_COMMAND]);
	}
	else if ((*tokens)->t_type == T_LPAR)
	{
		node[I_SUBSHELL] = subshell(tokens);
		if (!node[I_SUBSHELL])
			return (NULL);
		ast_add_child(node[I_COMMAND], node[I_SUBSHELL]);
		return (node[I_COMMAND]);
	}
	else if (!(*tokens) && (!((*tokens)->t_type == T_LPAR)
			|| !(is_word((*tokens)->t_type) || is_redi((*tokens)->t_type))))
		return (NULL);
	return (NULL);
}

t_ast_node	*pipeline(t_token **tokens)
{
	t_ast_node	*node[7];

	node[I_PIPELINE] = ast_new(G_PIPELINE, NULL);
	node[I_COMMAND] = command(tokens);
	if (!node[I_COMMAND])
		return (NULL);
	ast_add_child(node[I_PIPELINE], node[I_COMMAND]);
	if (*tokens && (*tokens)->t_type == T_PIPE)
	{
		*tokens = (*tokens)->next;
		if ((*tokens && !valid_pipe(tokens)) || !(*tokens))
			return (NULL);
	}
	return (node[I_PIPELINE]);
}

t_ast_node	*compound_command(t_token **tokens, bool in_subshell)
{
	t_ast_node	*node[7];

	node[I_COMPOUND_COMMAND] = ast_new(G_COMPOUND_COMMAND, NULL);
	while (*tokens)
	{
		node[I_PIPELINE] = pipeline(tokens);
		if (!node[I_PIPELINE] && *tokens && (*tokens)->t_type == T_RPAR
			&& is_operator((*tokens)->t_type) && in_subshell)
			return (ast_add_child(node[I_COMPOUND_COMMAND], node[I_PIPELINE]),
				node[I_COMPOUND_COMMAND]);
		else if (!node[I_PIPELINE])
			return (NULL);
		ast_add_child(node[I_COMPOUND_COMMAND], node[I_PIPELINE]);
		if (*tokens && is_and_or((*tokens)->t_type))
		{
			ast_add_child(node[I_COMPOUND_COMMAND],
				ast_new((t_grammar)(*tokens)->t_type, NULL));
			*tokens = (*tokens)->next;
			if ((*tokens && !valid_compound(tokens)) || !(*tokens))
				return (NULL);
		}
		else if (*tokens && !in_subshell && (*tokens)->t_type == T_RPAR)
			return (NULL);
	}
	return (node[I_COMPOUND_COMMAND]);
}
