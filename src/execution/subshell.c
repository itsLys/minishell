/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 11:23:43 by ihajji            #+#    #+#             */
/*   Updated: 2025/06/21 11:24:04 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int execute_subshell(t_ast_node *node, t_data *data)
{
	int pid;
	int status;

	pid = fork();
	if (pid == 0)
		exit(execute(node->child, data, true)); // clean exit
	else if (pid == ERROR)
		perror("fork"); // exit clean;
	waitpid(pid, &status, 0);
	return WEXITSTATUS(status);
}
