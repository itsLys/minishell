/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all_ast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 18:49:56 by zbengued          #+#    #+#             */
/*   Updated: 2025/07/03 19:11:05 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parsing.h>
#include <execution.h>

void	free_tokens(t_token **head)
{
	t_token	*next;
	t_token	*tmp;

	if (!head || !*head)
		return ;
	tmp = *head;
	while (tmp)
	{
		next = tmp->next;
		str_destroy(&tmp->val);
		free(tmp);
		tmp = next;
	}
	*head = NULL;
}

void	free_all_ast(t_ast_node *node)
{
	t_ast_node	*sibling;
	t_ast_node	*next;

	if (!node)
		return ;
	free_all_ast(node->child);
	sibling  = node->sibling;
	while (sibling)
	{
		next = sibling->sibling;
		free_all_ast(sibling);
		sibling = next;
	}
	str_destroy(&node->value);
	str_arr_destroy(&node->args);
	free(node);
}
