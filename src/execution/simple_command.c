/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 09:15:21 by ihajji            #+#    #+#             */
/*   Updated: 2025/06/21 09:21:17 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static int	execute_bin(char **argv, t_data *data, bool run_in_shell)
{
	pid_t		pid;
	int			status;

	if (run_in_shell)
		return ft_execvpe(argv[0], argv, make_envp(data->env));
	else
	{
		pid = fork();
		if (pid == 0)
			exit(ft_execvpe(argv[0], argv, make_envp(data->env))); // clean exit
		else if (pid == ERROR)
			perror("fork"); // clean exit
	}
	waitpid(pid, &status, 0);
	return status;
}

#include <fcntl.h>
#include <sys/stat.h>

int setup_redir_trunc(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_TRUNC | O_CREAT,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd == ERROR)
		return perror(file), ERROR;
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return SUCCESS;
}

int setup_redir_append(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_APPEND | O_CREAT,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd == ERROR)
		return perror(file), ERROR;
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return SUCCESS;
}

int setup_redir_heredoc(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == ERROR)
		return perror(file), ERROR;
	dup2(fd, STDIN_FILENO);
	close(fd);
	return SUCCESS;
}

int setup_redir_in(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == ERROR)
		return perror(file), ERROR;
	dup2(fd, STDIN_FILENO);
	close(fd);
	return SUCCESS;
}

int setup_redir(t_ast_node *redir)
{
	int status;

	status = 0;
	while (redir)
	{
		if (redir->type == G_REDI_TRUNC)
			status = setup_redir_trunc(redir->value);
		else if (redir->type == G_REDI_APPEND)
			status = setup_redir_append(redir->value);
		else if (redir->type == G_REDI_HEREDOC)
			status = setup_redir_heredoc(redir->value);
		else if (redir->type == G_REDI_IN)
			status = setup_redir_in(redir->value);
		if (status == ERROR)
			return ERROR;
		redir = redir->sibling;
	}
	return  SUCCESS;
}

int	execute_simple_command(t_ast_node *node, t_data *data, bool run_in_shell)
{
	char		**argv;
	t_builtin	*builtin;
	int			std_streams[2];
	int			status;


	// argv = extract_args(node->child->args);
	argv = node->child->args;
	std_streams[STDOUT_FILENO] = dup(STDOUT_FILENO);
	std_streams[STDIN_FILENO] = dup(STDIN_FILENO);
	if (node->child->sibling && setup_redir(node->child->sibling->child))
		return FAILIURE;
	builtin = find_builtin(argv[0]);
	if (builtin)
		status = builtin->function(argv, &(data->env), data);
	else
		if (run_in_shell)
			status = execute_bin(argv, data, run_in_shell);
		else
			status = WEXITSTATUS(execute_bin(argv, data, run_in_shell));;
	dup2(std_streams[STDOUT_FILENO], STDOUT_FILENO);
	dup2(std_streams[STDIN_FILENO], STDIN_FILENO);
	close(std_streams[STDOUT_FILENO]);
	close(std_streams[STDIN_FILENO]);
	return status;
}
