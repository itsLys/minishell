/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 07:49:18 by ihajji            #+#    #+#             */
/*   Updated: 2025/06/17 12:01:43 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#define STR "Hello"
#include <sys/types.h>
#include <sys/wait.h>

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
// NOTE: remove

#define PIPE_RD 0
#define PIPE_WR 1
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

void execute_first_pipeline(t_ast_node *pipeline, t_data *data, int pipefd[2])
{
	if (fork() == 0)
	{
		dup2(pipefd[PIPE_WR], STDOUT_FILENO);
		close(pipefd[PIPE_WR]);
		close(pipefd[PIPE_RD]);
		execute(pipeline->child, data, true);
	}
	// else
	// 	perror("fork"); // maybe exit clean
}

void execute_middle_pipeline(t_ast_node *pipeline, t_data *data, int pipefd[2])
{
	// read from the read end of the pipe instead of stdout
	// but only in child?
	// so
	// but also, write to the write end of a new pipe

	int saved = dup(STDIN_FILENO);
	close(pipefd[PIPE_WR]);
	dup2(pipefd[PIPE_RD], 0);
	close(pipefd[PIPE_RD]);
	pipe(pipefd);
	if (fork() == 0)
	{
		close(pipefd[PIPE_RD]);
		dup2(pipefd[PIPE_WR], 1);
		close(pipefd[PIPE_WR]);
		execute(pipeline->child, data, true);
	}
	dup2(saved, STDIN_FILENO);
	close(saved);
}

pid_t execute_last_pipeline(t_ast_node *pipeline, t_data *data, int pipefd[2])
{
	pid_t pid;
	pid = fork();
	if (pid == 0)
	{
		dup2(pipefd[PIPE_RD], STDIN_FILENO);
		close(pipefd[PIPE_WR]);
		close(pipefd[PIPE_RD]);
		execute(pipeline->child, data, true);
	}
	// else
	// 	perror("fork"); // maybe exit clean
	return pid;
}

int	execute_pipeline(t_ast_node *node, t_data *data/* , bool run_in_shell */) // should be generic
{
	t_ast_node *pipeline;
	int pipefd[2];
	pid_t last;

	pipe(pipefd);
	pipeline = node;
	if (is_single_pipeline(node))
		return (execute(pipeline->child, data, false));
	// printf("types\n");
	execute_first_pipeline(pipeline, data, pipefd);
	pipeline = pipeline->sibling;
	while (pipeline && pipeline->type == G_PIPELINE
			&& pipeline->sibling && pipeline->sibling->type == G_PIPELINE)
	{
		execute_middle_pipeline(pipeline, data, pipefd);
		pipeline = pipeline->sibling;
	}
	last = execute_last_pipeline(pipeline, data, pipefd);
	close(pipefd[PIPE_RD]);
	close(pipefd[PIPE_WR]);
	waitpid(last, NULL, 0);
	while (wait(NULL) != ERROR)
		;
	// printf("end types\n");
	return 0;
}

// BUG: exit (builtin) cuases double free

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
