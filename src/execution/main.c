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

int	execute(t_ast_node *node, t_data *data, bool run_in_shell)
{
	if (node->type == G_SUBSHELL)
		return (execute_subshell(node, data));
	else if (node->type == G_COMPOUND_COMMAND)
		return (execute_compound(node, data));
	else if (node->type == G_PIPELINE)
		return (execute_pipeline(node, data));
	else if (node->type == G_COMMAND)
		return (execute(node->child, data, run_in_shell));
	else if (node->type == G_SIMPLE_COMMAND)
		return (execute_simple_command(node, data, run_in_shell));
	return (SUCCESS);
}
