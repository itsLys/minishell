/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 07:49:18 by ihajji            #+#    #+#             */
/*   Updated: 2025/06/01 08:02:32 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void execute_compound(t_ast_node *node)
{
	execute_pipeline(node);
}

void	execute(t_ast_node *node)
{
	if (node->type == G_COMPOUND_COMMAND)
		execute_compound(node->child);
}
