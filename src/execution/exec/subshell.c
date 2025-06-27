/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 11:23:43 by ihajji            #+#    #+#             */
/*   Updated: 2025/06/21 11:32:50 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int execute_subshell(t_ast_node *node, t_data *data)
{
	int	pid;
	int	std_io[2];
	int	status;

	std_io[STDOUT_FILENO] = dup(STDOUT_FILENO);
	std_io[STDIN_FILENO] = dup(STDIN_FILENO);
	if (node->child->sibling && setup_redir(node->child->sibling->child))
		return FAILIURE;
	pid = fork();
	if (pid == 0)
		exit(execute(node->child, data, true)); // clean exit
	else if (pid == ERROR)
		perror("fork"); // exit clean;
	waitpid(pid, &status, 0);
	dup2(std_io[STDOUT_FILENO], STDOUT_FILENO);
	dup2(std_io[STDIN_FILENO], STDIN_FILENO);
	close(std_io[STDOUT_FILENO]);
	close(std_io[STDIN_FILENO]);
	return WEXITSTATUS(status);
}
