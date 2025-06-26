/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 12:20:58 by zbengued          #+#    #+#             */
/*   Updated: 2025/05/31 20:27:15 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stdio.h>

void	print_tokens(t_token *tokens)
{
	while (tokens)
	{
		printf("Type: %s", tokens->type);
		if (tokens->val)
			printf(" | Value: %s", tokens->val);
		printf("\n");
		tokens = tokens->next;
	}
}


void	print_token(t_token *token)
{
	printf("val ; %s\ntype ; %s\n", token->val, token->type);
}

// void	ast_print(t_ast_node *node, size_t depth, const char *prefix, int is_last)
// {
// 	char	new_prefix[256];
// 	const char *branch = is_last ? "└── " : "├── ";
// 	const char *next_prefix = is_last ? "    " : "│   ";
//
// 	if (!node)
// 		return;
// 	printf("%s%s", prefix, branch);
// 	switch (node->type) {
// 		case G_COMPOUND_COMMAND: printf("G_COMPOUND_COMMAND"); break;
// 		case G_PIPELINE: printf("G_PIPELINE"); break;
// 		case G_COMMAND: printf("G_COMMAND"); break;
// 		case G_SUBSHELL: printf("G_SUBSHELL"); break;
// 		case G_SIMPLE_COMMAND: printf("G_SIMPLE_COMMAND"); break;
// 		case G_ARGS: printf("G_ARGS"); break;
// 		case G_REDI_IN: printf("G_REDIR_IN"); break;
// 		case G_REDI_TRUNC: printf("G_REDI_TRUNC"); break;
// 		case G_REDI_APPEND: printf("G_REDI_APPEND"); break;
// 		case G_REDI_HEREDOC: printf("G_REDI_HEREDOC"); break;
// 		case G_REDIRECT_LIST: printf("G_REDIRECT_LIST"); break;
// 		case G_IO_REDIRECT: printf("G_IO_REDIRECT"); break;
// 		case G_AND_NODE: printf("G_AND_NODE"); break;
// 		case G_OR_NODE: printf("G_OR_NODE"); break;
// 		default: printf("UNKNOWN"); break;
// 	}
// 	if (node->value)
// 		printf(" (value: %s)", node->value);
// 	else if (node->args)
// 		print_2d_array(node->args);
// 	printf("\n");
// 	snprintf(new_prefix, sizeof(new_prefix), "%s%s", prefix, next_prefix);
// 	t_ast_node *child = node->child;
// 	while (child) {
// 		t_ast_node *next = child->sibling;
// 		ast_print(child, depth + 1, new_prefix, next == NULL);
// 		child = next;
// 	}
// }
void	ast_print(t_ast_node *node, size_t depth, const char *prefix, int is_last)
{
	char	new_prefix[256];
	const char *branch = is_last ? "└── " : "├── ";
	const char *next_prefix = is_last ? "    " : "│   ";

	if (!node)
		return;
	printf("%s%s", prefix, branch);
	switch (node->type) {
		case G_COMPOUND_COMMAND: printf("G_COMPOUND_COMMAND"); break;
		case G_PIPELINE: printf("G_PIPELINE"); break;
		case G_COMMAND: printf("G_COMMAND"); break;
		case G_SUBSHELL: printf("G_SUBSHELL"); break;
		case G_SIMPLE_COMMAND: printf("G_SIMPLE_COMMAND"); break;
		case G_ARGS: printf("G_ARGS"); break;
		case G_REDI_IN: printf("G_REDI_IN"); break;
		case G_REDI_TRUNC: printf("G_REDI_TRUNC"); break;
		case G_REDI_APPEND: printf("G_REDI_APPEND"); break;
		case G_REDI_HEREDOC: printf("G_REDI_HEREDOC"); break;
		case G_REDIRECT_LIST: printf("G_REDIRECT_LIST"); break;
		case G_IO_REDIRECT: printf("G_IO_REDIRECT"); break;
		case G_AND_NODE: printf("G_AND_NODE"); break;
		case G_OR_NODE: printf("G_OR_NODE"); break;
		default: printf("UNKNOWN"); break;
	}
	if (node->value)
		printf(" (value: %s)", node->value);
	if (node->type == G_ARGS && node->args)
	{
		for (int i = 0; node->args[i]; i++)
		{
			printf("%s [%s]", prefix, node->args[i]);
			// printf("[%s]", node->mask[i]);
		}

	}
	printf("\n");
	snprintf(new_prefix, sizeof(new_prefix), "%s%s", prefix, next_prefix);
	t_ast_node *child = node->child;
	while (child)
	{
		t_ast_node *next = child->sibling;
		ast_print(child, depth + 1, new_prefix, next == NULL);
		child = next;
	}
}
