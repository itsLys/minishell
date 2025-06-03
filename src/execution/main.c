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

bool	is_n_flaged(char *arg)
{
	int i;

	i = 1;
	if (!arg || arg[0] == '-')
		return false;
	if (arg[i] == 'n')
		i++;
	while (arg[i] == 'n')
		i++;
	return arg[i] == '\0';
}

int	echo(char **argv)
{
	int	n_flaged;
	int	i;
	
	i = 1;
	n_flaged = is_n_flaged(argv[i]);
	if (n_flaged)
		i++;
	while (is_n_flaged(argv[i]))
		printf("%s:::", argv[i++]);
	while (argv[i])
	{
		printf("%s", argv[i++]);
		if (argv[i])
			printf(" ");
	}
	if (!n_flaged)
		printf("\n");
	return 0;
}

int	cd(char **argv)
{
	(void)argv; printf("hello from %s", "cd"); return 0;
}

int	pwd(char **argv)
{
	(void)argv; printf("hello from %s", "pwd"); return 0;
}

int	export(char **argv)
{
	(void)argv; printf("hello from %s", "export"); return 0;
}

int	unset(char **argv)
{
	(void)argv; printf("hello from %s", "unset"); return 0;
}

int env(char **argv)
{
	(void)argv; printf("hello from %s", "env"); return 0;
}

int	ft_exit(char **argv)
{
	(void)argv; printf("hello from %s", "ft_exit"); return 0;
}

t_builtin	*init_builtins(void)
{
	static t_builtin builtin[] = {
		{"echo", &echo},
		{"cd", &cd},
		{"pwd", &pwd},
		{"export", &export},
		{"unset", &unset},
		{"env", &env},
		{"exit", &ft_exit},
		{0},
	};
	return builtin;
}

// char **extract_args(char **args)
// {
// 	char **argv;
// 	int i = 0;
//
// 	while (args[i])
// 		i++;
//
// 	argv = malloc((i + 1) * sizeof(char *));
//
// }

int	find_builtin(char *cmd)
{
	int i = 0;
	while (g_data.builtins[i].name)
	{
		if (ft_strcmp(cmd, g_data.builtins[i].name) == 0)
			return i;
		i++;
	}
	return ERROR;
}

int	execute_simple_command(t_ast_node *node)
{
	char **argv;

	// argv = extract_args(node->child->args);
	// setup_redir(node->child->sibling);

	argv = node->child->args;
	int	builtin_index;
	if ((builtin_index = find_builtin(argv[0])) != ERROR)
		return g_data.builtins[builtin_index].function(argv);
	else
	{
		if (fork() == 0)
			ft_execvpe(argv[0], argv, g_data.env);
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
	g_data.status = execute(node->child);
	return g_data.status;
}

int	execute(t_ast_node *node)
{
	g_data.builtins = init_builtins(); // TODO: Move to a sutable place; initialization perhaps
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
