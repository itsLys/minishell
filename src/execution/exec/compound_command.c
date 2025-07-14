/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compound_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 09:16:11 by ihajji            #+#    #+#             */
/*   Updated: 2025/06/21 11:32:50 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static bool	resolve_logical(int status, t_ast_node *node)
{
	if (node && node->type == G_AND_NODE)
	{
		node = node->sibling;
		if (status == SUCCESS)
			return (true);
		return (false);
	}
	else if (node && node->type == G_OR_NODE)
	{
		node = node->sibling;
		if (status == SUCCESS)
			return (false);
		return (true);
	}
	return (false);
}

int	execute_compound(t_ast_node *node, t_data *data)
{
	int			status;
	bool		should_execute;
	t_ast_node	*child;

	child = node->child;
	status = 0;
	should_execute = true;
	while (child)
	{
		if (child->type == G_PIPELINE && should_execute == true)
			status = execute(child, data, false);
		while (child && child->type == G_PIPELINE)
			child = child->sibling;
		if (child)
		{
			should_execute = resolve_logical(status, child);
			child = child->sibling;
		}
	}
	return (status);
}
