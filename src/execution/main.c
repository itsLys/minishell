/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 07:49:18 by ihajji            #+#    #+#             */
/*   Updated: 2025/06/21 11:31:09 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

// debuging

void    print_ast_type(t_ast_node *node)
{
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
	printf("\n");
}

// BUG: exit (builtin) cuases double free
// BUG: cd as a last command in a pipeline returns CMD_NOT_FOUND
// BUG: exit NON should exit with last exit status

int	execute(t_ast_node *node, t_data *data, bool run_in_shell)
{
	if (node->type == G_SUBSHELL)
		return (execute_subshell(node, data));
	else if (node->type == G_COMPOUND_COMMAND)
		return (execute_compound(node, data));
	else if (node->type == G_PIPELINE)
		return (execute_pipeline(node, data/* , run_in_shell */));
	else if (node->type == G_COMMAND)
		return (execute(node->child, data, run_in_shell));
	else if (node->type == G_SIMPLE_COMMAND)
		return execute_simple_command(node, data, run_in_shell);
	return (SUCCESS);
}
