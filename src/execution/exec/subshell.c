/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 11:23:43 by ihajji            #+#    #+#             */
/*   Updated: 2025/07/13 12:55:09 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	execute_subshell(t_ast_node *node, t_data *data)
{
	int	pid;
	int	stdio[2];
	int	status;

	save_stdio(stdio, data);
	if (node->child->sibling
		&& setup_redir(node->child->sibling->child, data))
		return (restore_stdio(stdio), FAILIURE);
	pid = fork();
	if (pid == 0)
	{
		status = execute(node->child, data, true);
		restore_stdio(stdio);
		clean_exit(status, data);
	}
	else if (pid == ERROR)
	{
		perror("fork");
		clean_exit(FAILIURE, data);
	}
	waitpid(pid, &status, 0);
	restore_stdio(stdio);
	return (WEXITSTATUS(status));
}
