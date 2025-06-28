/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 12:47:30 by ihajji            #+#    #+#             */
/*   Updated: 2025/06/26 12:48:51 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static int setup_redir_trunc(char *file)
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

static int setup_redir_append(char *file)
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

static int setup_redir_heredoc(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == ERROR)
		return perror(file), ERROR;
	dup2(fd, STDIN_FILENO);
	close(fd);
	return SUCCESS;
}

static int setup_redir_in(char *file)
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
			status = setup_redir_trunc(redir->value.data);
		else if (redir->type == G_REDI_APPEND)
			status = setup_redir_append(redir->value.data);
		else if (redir->type == G_REDI_HEREDOC)
			status = setup_redir_heredoc(redir->value.data);
		else if (redir->type == G_REDI_IN)
			status = setup_redir_in(redir->value.data);
		if (status == ERROR)
			return ERROR;
		redir = redir->sibling;
	}
	return  SUCCESS;
}
