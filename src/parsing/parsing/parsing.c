/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 16:27:18 by zbengued          #+#    #+#             */
/*   Updated: 2025/06/30 18:17:05 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stddef.h>

void	syntax_err(t_token **tokens, t_ast_node *node)
{
	g_interrupted[2] = 2;
	ft_dprintf(STDERR, "SYNTAX ERROR\n");
	free_tokens(tokens);
	*tokens = NULL;
	free_all_ast(node);
}

t_ast_node	*simple_command(t_token **tokens)
{
	t_ast_node	*node[7];

	node[I_RED_LIST] = ast_new(G_REDIRECT_LIST, NULL);
	node[I_ARGLIST] = ast_new(G_ARGS, NULL);
	while (*tokens && is_word_or_redir((*tokens)->t_type))
	{
		if (is_word((*tokens)->t_type))
			consume_word(tokens, node[I_ARGLIST]);
		else if (*tokens && is_redi((*tokens)->t_type))
			consume_redir(tokens, node[I_RED_LIST]);
		else if (!(*tokens) || !is_word_or_redir((*tokens)->t_type))
			break ;
		if (g_interrupted[HEREDOC_INTERRUPT])
			return (free_all_ast(node[I_RED_LIST]),
					free_all_ast(node[I_ARGLIST]), NULL);
	}
	if ((*tokens && (*tokens)->t_type == T_LPAR))
		return (free_all_ast(node[I_RED_LIST]), free_all_ast(node[I_ARGLIST]),
			NULL);
	node[I_SIMPLE_COMMAND] = ast_new(G_SIMPLE_COMMAND, NULL);
	return (ast_add_child(node[I_SIMPLE_COMMAND], node[I_ARGLIST]),
		ast_add_child(node[I_SIMPLE_COMMAND], node[I_RED_LIST]),
		node[I_SIMPLE_COMMAND]);
}

t_ast_node	*subshell(t_token **tokens)
{
	t_ast_node	*node[7];

	delete_token(tokens);
	if ((!(*tokens) || is_and_or((*tokens)->t_type)) || (*tokens)->t_type == T_RPAR)
		return (NULL);
	node[I_COMPOUND_COMMAND] = compound_command(tokens, true);
	if (!node[I_COMPOUND_COMMAND] || !(*tokens))
		return (free_all_ast(node[I_COMPOUND_COMMAND]), NULL);
	delete_token(tokens);
	if (*tokens && (is_word((*tokens)->t_type) || (*tokens)->t_type == T_LPAR))
		return (NULL);
	node[I_RED_LIST] = ast_new(G_REDIRECT_LIST, NULL);
	while (*tokens && is_redi((*tokens)->t_type))
		consume_redir(tokens, node[I_RED_LIST]);
	node[I_SUBSHELL] = ast_new(G_SUBSHELL, NULL);
	ast_add_child(node[I_SUBSHELL], node[I_COMPOUND_COMMAND]);
	ast_add_child(node[I_SUBSHELL], node[I_RED_LIST]);
	return (node[I_SUBSHELL]);
}

t_ast_node	*command(t_token **tokens)
{
	t_ast_node	*node[7];

	if (is_word((*tokens)->t_type) || is_redi((*tokens)->t_type))
	{
		node[I_SIMPLE_COMMAND] = simple_command(tokens);
		if (!node[I_SIMPLE_COMMAND])
			return (NULL);
		node[I_COMMAND] = ast_new(G_COMMAND, NULL);
		ast_add_child(node[I_COMMAND], node[I_SIMPLE_COMMAND]);
		return (node[I_COMMAND]);
	}
	else if ((*tokens)->t_type == T_LPAR)
	{
		node[I_SUBSHELL] = subshell(tokens);
		if (!node[I_SUBSHELL])
			return (NULL);
		node[I_COMMAND] = ast_new(G_COMMAND, NULL);
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

	node[I_COMMAND] = command(tokens);
	if (!node[I_COMMAND])
		return (NULL);
	node[I_PIPELINE] = ast_new(G_PIPELINE, NULL);
	ast_add_child(node[I_PIPELINE], node[I_COMMAND]);
	if (*tokens && (*tokens)->t_type == T_PIPE)
	{
		delete_token(tokens);
		if ((*tokens && !valid_pipe(tokens)) || !(*tokens))
			return (syntax_err(tokens, node[I_PIPELINE]), NULL);
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
			return (syntax_err(tokens, node[I_COMPOUND_COMMAND]), NULL);
		ast_add_child(node[I_COMPOUND_COMMAND], node[I_PIPELINE]);
		if (*tokens && is_and_or((*tokens)->t_type))
		{
			ast_add_child(node[I_COMPOUND_COMMAND],
				ast_new((t_grammar)(*tokens)->t_type, NULL));
			delete_token(tokens);
			if ((*tokens && !valid_compound(tokens)) || !(*tokens))
				return (syntax_err(tokens, node[I_COMPOUND_COMMAND]), NULL);
		}
		// else if (*tokens && !in_subshell && (*tokens)->t_type == T_LPAR)
		// 	return (printf("here!!!!!! 2\n"), NULL);
	}
	return (node[I_COMPOUND_COMMAND]);
}
