/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 07:49:18 by ihajji            #+#    #+#             */
/*   Updated: 2025/06/13 16:08:20 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#define STR "Hello"

int	execute_simple_command(t_ast_node *node, t_data *data)
{
	char		**argv;
	t_builtin	*builtin;

	// argv = extract_args(node->child->args);
	// setup_redir(node->child->sibling);
	argv = node->child->args;
	builtin = find_builtin(argv[0]);
	if (builtin)
		return (builtin->function(argv, &(data->env), data));
	else
	{
		// execute binary
		// if (fork() == 0)
		// 	ft_execvpe(argv[0], argv, g_data()->env);
	}
	return (127);
}

int	execute_command(t_ast_node *node, t_data *data)
{
	return (execute(node->child, data));
}

int	execute_pipeline(t_ast_node *node, t_data *data)
{
	return (execute(node->child, data));
}

int	execute_compound(t_ast_node *node, t_data *data)
{
	int	status;

	status = execute(node->child, data);
	return (status);
}

int	execute(t_ast_node *node, t_data *data)
{
	if (node->type == G_COMPOUND_COMMAND)
		return (execute_compound(node, data));
	else if (node->type == G_PIPELINE)
		return (execute_pipeline(node, data));
	else if (node->type == G_COMMAND)
		return (execute_command(node, data));
	else if (node->type == G_SIMPLE_COMMAND)
		execute_simple_command(node, data);
	return (SUCCESS);
}
