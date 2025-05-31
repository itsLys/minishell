/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 15:24:46 by zbengued          #+#    #+#             */
/*   Updated: 2025/05/18 18:14:57 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parsing.h>

t_ast_node	*ast_new(t_grammar type, char *value)
{
	t_ast_node	*node;

	node = malloc(sizeof(t_ast_node));
	node->type = type;
	node->value = value;
	node->child = NULL;
	node->sibling = NULL;
	node->args = NULL;
	return (node);
}

void	ast_add_child(t_ast_node *parent, t_ast_node *child)
{
	t_ast_node	*current;

	if (!parent->child)
		parent->child = child;
	else
	{
		current = parent->child;
		while (current->sibling)
			current = current->sibling;
		current->sibling = child;
	}
}

void	ast_free(t_ast_node *node)
{
	t_ast_node	*next;

	while (node)
	{
		next = node->sibling;
		if (node->child)
			ast_free(node->child);
		free(node->value);
		free(node);
		node = next;
	}
}
