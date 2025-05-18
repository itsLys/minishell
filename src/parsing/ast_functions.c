/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 15:24:46 by zbengued          #+#    #+#             */
/*   Updated: 2025/04/25 19:00:04 by zbengued         ###   ########.fr       */
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
//
// int main(void)
// {
// 	t_ast_node *cmd1 = ast_new(G_SIMPLE_COMMAND, ft_strdup("echo hello"));
// 	t_ast_node *cmd2 = ast_new(G_SIMPLE_COMMAND, ft_strdup("ls"));
// 	t_ast_node *cmd3 = ast_new(G_SIMPLE_COMMAND, ft_strdup("grep txt"));
//
// 	t_ast_node *pipe = ast_new(G_PIPELINE, NULL);
// 	ast_add_child(pipe, cmd2);
// 	ast_add_child(pipe, cmd3);
// 	
//
// 	t_ast_node *and_node = ast_new(G_COMPOUND_COMMAND, NULL);
// 	ast_add_child(and_node, cmd1);
// 	t_ast_node *and = ast_new(G_AND_NODE, NULL);
// 	ast_add_child(and_node, and);
// 	ast_add_child(and_node, pipe);
//
// 	ast_print(and_node, 0, "", 1);
// 	ast_free(and_node);
// 	return 0;
// }
