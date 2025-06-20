/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 07:49:18 by ihajji            #+#    #+#             */
/*   Updated: 2025/06/18 16:41:38 by ihajji           ###   ########.fr       */
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

<<<<<<< HEAD
// BUG: cd as a last command in a pipeline returns CMD_NOT_FOUND
// BUG: exit NON should exit with last exit status
char **make_envp(t_env *env)
{
	int len;
	int i;
	char **envp;

	len = env_count_len(env);
	envp = malloc(sizeof(char *) * (len + 1)); // NOTE: check malloc
	i = 0;
	while (env)
	{
		if (env->exported)
			envp[i++] = make_name_eq_value(env->name, env->value);
		env = env->next;
	}
	envp[i] = NULL;
	return envp;
}

int	execute_simple_command(t_ast_node *node, t_data *data, bool run_in_shell)
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
		return WEXITSTATUS(execute_bin(argv, data, run_in_shell));
}

int	execute_command(t_ast_node *node, t_data *data, bool run_in_shell)
{
	return (execute(node->child, data, run_in_shell));
}
// BUG: exit (builtin) cuases double free
//
int	execute_logical_and(int status, t_ast_node *node, t_data *data, bool run_in_shell)
{
	if (status == SUCCESS)
		return execute(node, data, run_in_shell);
	return status;
}

int	execute_logical_or(int status, t_ast_node *node, t_data *data, bool run_in_shell)
{

	if (status == SUCCESS)
		return status;
	return execute(node, data, run_in_shell);
}

int	execute_compound(t_ast_node *node, t_data *data)
{
	int	status;
	bool should_execute;
	t_ast_node *child;

	child = node->child;
	status = 0;
	should_execute = true;
	while (child)
	{
		if (child->type == G_PIPELINE && should_execute == true)
			status = execute(child, data, false);
		while (child && child->type == G_PIPELINE)
			child = child->sibling;
		if (child && child->type == G_AND_NODE)
		{
			child = child->sibling;
			if (status == SUCCESS)
				should_execute = true;
		}
		else if (child && child->type == G_OR_NODE)
		{
			child = child->sibling;
			if (status == SUCCESS)
				should_execute = false;
		}
		if (child)
			print_ast_type(child);
	}
	return status;
}

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
