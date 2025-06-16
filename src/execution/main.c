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
#include <sys/types.h>
#include <sys/wait.h>

char *make_name_eq_value(char *name, char *value)
{
	// NOTE: CHECK MALLOC
	char *name_eq;
	char *name_eq_value;

	name_eq = ft_strjoin(name, "=");
	name_eq_value = ft_strjoin(name_eq, value);
	free(name_eq);
	return name_eq_value;
}

int	env_count_len(t_env *env)
{
	int i;

	i = 0;
	while (env)
	{
		if (env->exported)
			i++;
		env = env->next;
	}
	return i;
}

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
	{
		if (run_in_shell)
			ft_execvpe(argv[0], argv, make_envp(data->env));
		else
		{
			if (fork() == 0)
				ft_execvpe(argv[0], argv, make_envp(data->env));
			else
				wait(NULL);
		}
	}
	return (127);
}

int	execute_command(t_ast_node *node, t_data *data, bool run_in_shell)
{
	return (execute(node->child, data, run_in_shell));
}

bool	is_single_pipeline(t_ast_node *node)
{
	return node && node->type == G_PIPELINE && (node->sibling == NULL || node->sibling->type != G_PIPELINE);
}

int	execute_pipeline(t_ast_node *node, t_data *data/* , bool run_in_shell */)
{
	pid_t pid1;
	pid_t pid2;
	int pipefd[2];

	if (is_single_pipeline(node))
		return (execute(node->child, data, false));

	if (pipe(pipefd))
		perror("perror"), exit(1);
	// spawn first pipeline
	if ((pid1 = fork()) == 0)
	{
		dup2(pipefd[1], 1);
		close(pipefd[0]);
		close(pipefd[1]);
		exit(execute(node->child, data, true));
	}
	if ((pid2 = fork()) == 0)
	{
		dup2(pipefd[0], 0);
		close(pipefd[0]);
		close(pipefd[1]);
		exit(execute(node->sibling->child, data, true));
	}

	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return 0;
}

int	execute_compound(t_ast_node *node, t_data *data, bool run_in_shell)
{
	int	status;

	status = execute(node->child, data, run_in_shell);
	return (status);
}

int	execute(t_ast_node *node, t_data *data, bool run_in_shell)
{
	if (node->type == G_COMPOUND_COMMAND)
		return (execute_compound(node, data, run_in_shell));
	else if (node->type == G_PIPELINE)
		return (execute_pipeline(node, data/* , run_in_shell */));
	else if (node->type == G_COMMAND)
		return (execute_command(node, data, run_in_shell));
	else if (node->type == G_SIMPLE_COMMAND)
		execute_simple_command(node, data, run_in_shell);
	return (SUCCESS);
}
