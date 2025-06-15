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
#define STR "Hello"

// find_var ; strchr(str, '$'); -> 

char	*find_var(char *arg)
{
	size_t	i;
	char *var_start;

	i = 0;
	var_start = ft_strchr(arg, '$');
	while (var_start[++i] && ft_isalnum(var_start[i]))
		;
	return (ft_strndup(var_start, i));
}

// char	**extract_args(char **og_args, char **env)
// {
// 	
// }

int	execute_simple_command(t_ast_node *node)
{
	char **argv;

	// argv = extract_args(node->child->args);
	// setup_redir(node->child->sibling);

	argv = node->child->args;
	int	builtin_index;
	if ((builtin_index = find_builtin(argv[0])) != ERROR)
		return g_data()->builtins[builtin_index].function(argv);
	else
	{
		// if (fork() == 0)
		// 	ft_execvpe(argv[0], argv, g_data()->env);
	}
	return 127;
}

int	execute_command(t_ast_node *node)
{
	return execute(node->child);
}

int	execute_pipeline(t_ast_node *node)
{
	return execute(node->child);
}

int execute_compound(t_ast_node *node)
{
	g_data()->status = execute(node->child);
	return g_data()->status;
}

int	execute(t_ast_node *node)
{
	g_data()->builtins = init_builtins(); // TODO: Move to a sutable place; initialization perhaps
	if (node->type == G_COMPOUND_COMMAND)
		return execute_compound(node);
	else if (node->type == G_PIPELINE)
		return execute_pipeline(node);
	else if (node->type == G_COMMAND)
		return execute_command(node);
	else if (node->type == G_SIMPLE_COMMAND)
		execute_simple_command(node);
	return SUCCESS;
}
