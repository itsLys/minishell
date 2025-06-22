/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:58:41 by ihajji            #+#    #+#             */
/*   Updated: 2025/06/18 16:05:25 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static bool	is_single_pipeline(t_ast_node *node)
{
	return node && node->type == G_PIPELINE && (node->sibling == NULL || node->sibling->type != G_PIPELINE);
}

static void execute_first_pipeline(t_ast_node *pipeline, t_data *data, int pipefd[2])
{
	pid_t pid;

	pid = fork();
	if (pid == 0)
	{
		dup2(pipefd[PIPE_WR], STDOUT_FILENO);
		close(pipefd[PIPE_WR]);
		close(pipefd[PIPE_RD]);
		exit(execute(pipeline->child, data, true));
	}
	else if (pid == ERROR)
		perror("fork"); // maybe exit clean
}

static void execute_middle_pipeline(t_ast_node *pipeline, t_data *data, int pipefd[2])
{
	pid_t pid;
	int saved_stdin;

	saved_stdin = dup(STDIN_FILENO);
	dup2(pipefd[PIPE_RD], STDIN_FILENO);
	close(pipefd[PIPE_WR]);
	close(pipefd[PIPE_RD]);
	pipe(pipefd);
	pid = fork();
	if (pid == 0)
	{
		dup2(pipefd[PIPE_WR], STDOUT_FILENO);
		close(pipefd[PIPE_RD]);
		close(pipefd[PIPE_WR]);
		exit(execute(pipeline->child, data, true));
	}
	else if (pid == ERROR)
		perror("fork"); // maybe exit clean
	dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdin);
}

static pid_t execute_last_pipeline(t_ast_node *pipeline, t_data *data, int pipefd[2])
{
	pid_t pid;

	pid = fork();
	if (pid == 0)
	{
		dup2(pipefd[PIPE_RD], STDIN_FILENO);
		close(pipefd[PIPE_WR]);
		close(pipefd[PIPE_RD]);
		exit(execute(pipeline->child, data, true));
	}
	else if (pid == ERROR)
		perror("fork"); // maybe exit clean
	return pid;
}

int	execute_pipeline(t_ast_node *node, t_data *data/* , bool run_in_shell */) // should be generic
{
	t_ast_node *pipeline;
	int pipefd[2];
	pid_t last;
	int status;

	pipe(pipefd);
	pipeline = node;
	if (is_single_pipeline(node))
		return (execute(pipeline->child, data, false));
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
	waitpid(last, &status, 0);
	printf("%d\n", status);
	while (wait(NULL) != ERROR)
		;
	return WEXITSTATUS(status);
}
