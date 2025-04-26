/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 16:27:18 by zbengued          #+#    #+#             */
/*   Updated: 2025/04/25 19:06:41 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <parsing.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

// t_ast_node	*simple_command(t_token **tokens)
// {
// 	t_ast_node	*node;
// 	t_ast_node	*last_arg;
// 	t_token		*tmp;
//
// 	// printf("in simple command\n");
// 	last_arg = NULL;
// 	tmp = *tokens;
// 	if (!tmp || tmp->t_type != T_WORD)
// 		return (NULL);
// 	node = ast_new(G_SIMPLE_COMMAND, tmp->val);
// 	*tokens = tmp->next;
// 	tmp = *tokens;
//
// 	while (tmp && tmp->t_type == T_WORD)
// 	{
// 		t_ast_node *arg = ast_new(G_SIMPLE_COMMAND, tmp->val);
// 		if (!last_arg)
// 			node->child = arg;
// 		else
// 			last_arg->sibling = arg;
// 		last_arg = arg;
// 		*tokens = tmp->next;
// 		tmp = *tokens;
// 	}
// 	return node;
// }
//
// t_ast_node	*command(t_token **tokens)
// {
// 	t_ast_node	*child;
//
// 	// printf("in command\n");
// 	// child = subshell(tokens);
// 	child = NULL;
// 	if (!child)
// 		child = simple_command(tokens);
// 	return (child);
// }
//
// t_ast_node	*pipeline(t_token **tokens)
// {
// 	t_ast_node	*child;
// 	t_ast_node	*node;
// 	t_token		*tmp;
//
// 	// printf("in pipeline\n");
// 	child = command(tokens);
// 	if (!child)
// 		return (NULL);
// 	tmp = *tokens;
// 	if (tmp && tmp->t_type == T_PIPE)
// 	{
// 		node = ast_new(G_PIPELINE, NULL);
// 		if (!node)
// 			return (NULL);
// 		node->value = ft_strdup(tmp->val);
// 		*tokens = tmp->next;
// 		node->child = child;
// 		child->sibling = pipeline(tokens);
// 		return (node);
// 	}
// 	return (child);
// }
//
// t_ast_node	*compound_command(t_token **tokens)
// {
// 	t_ast_node	*child;
// 	t_ast_node	*node;
// 	t_token		*tmp;
//
// 	// printf("in compound command\n");
// 	while (true)
// 	{
// 		child = pipeline(tokens);
// 		if (!child)
// 			return (NULL);
// 		tmp = *tokens;
// 		if (tmp && (tmp->t_type == T_OR || tmp->t_type == T_AND))
// 		{
// 			node = ast_new(G_COMPOUND_COMMAND, NULL);
// 			if (!node)
// 				return (NULL);
// 			node->value = ft_strdup(tmp->val);
// 			*tokens = tmp->next;
// 			node->child = child;
// 			child->sibling = compound_command(tokens);
// 			return (node);
// 		}
// 	}
// 	return (child);
// }
//

t_ast_node	*simple_command(t_token **tokens)
{
	// t_ast_node	*simple_command;
	// t_token		*arg_list;
	// t_token		*redirections;
	
	(void)tokens;
	return (ast_new(G_COMMAND, "haha"));
}

t_ast_node	*command(t_token **tokens)
{
	t_token		*token;
	t_ast_node	*subshell_node;
	t_ast_node	*command;

	command = ast_new(G_COMMAND, NULL);

	token = *tokens;
	if (token->t_type == T_LPAR)
		subshell(tokens);
	return (simple_command(tokens));
}

t_ast_node	*pipeline(t_token **tokens)
{
	t_token		*token;
	t_ast_node	*pipes;
	t_ast_node	*command_node;
	
	pipes = ast_new(G_PIPELINE, NULL);
	while(true)
	{
		command_node = command(tokens);
		if (!command_node)
			return (NULL);
		ast_add_child(pipes, command_node);
		token = *tokens;
		if (token && token->t_type == T_PIPE)
			*tokens = (*tokens)->next;
		else
			break ;
	}
	return (pipes);
}

t_ast_node	*compound_command(t_token **tokens)
{
	t_ast_node	*pipes;
	t_ast_node	*compounds;
	t_token		*tmp;
	
	compounds = ast_new(G_COMPOUND_COMMAND, NULL);
	while(true)
	{
		pipes = pipeline(tokens);
		if (!pipes)
			return (NULL);
		ast_add_child(compounds, pipes);
		tmp = *tokens;
		if (tmp && (tmp->t_type == T_OR || tmp->t_type == T_AND))
		{
			ast_add_child(compounds, ast_new(G_OR_NODE, NULL));
			*tokens = (*tokens)->next;
		}
		else
			break ;
	}
	return (compounds);
}
