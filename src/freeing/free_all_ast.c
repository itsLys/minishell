/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all_ast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 18:49:56 by zbengued          #+#    #+#             */
/*   Updated: 2025/07/14 14:40:36 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parsing.h>
#include <execution.h>

void	delete_token(t_token **head)
{
	t_token	*tmp;

	tmp = (*head)->next;
	str_destroy(&(*head)->val);
	free(*head);
	*head = tmp;
}

void	free_tokens(t_token **head)
{
	t_token	*tmp;

	if (!head || !*head)
		return ;
	tmp = *head;
	while (tmp)
		delete_token(&tmp);
	*head = NULL;
}

void	free_all_ast(t_ast_node *node)
{
	t_ast_node	*sibling;
	t_ast_node	*child;

	if (!node)
		return ;
	child = node->child;
	sibling = node->sibling;
	str_destroy(&node->value);
	str_arr_destroy(&node->args);
	free(node);
	free_all_ast(child);
	free_all_ast(sibling);
}
