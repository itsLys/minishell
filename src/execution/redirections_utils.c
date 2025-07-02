/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 18:38:36 by ihajji            #+#    #+#             */
/*   Updated: 2025/07/02 18:38:41 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int save_stdio(int stdio[2], t_data *data)
{
	int	stdin;
	int	stdout;

	stdout = dup(STDOUT_FILENO);
	stdin = dup(STDIN_FILENO);
	if (stdout == ERROR || stdin == ERROR)
		return perror("dup"), clean_exit(FAILIURE, data), FAILIURE;
	stdio[STDOUT_FILENO] =  stdout;
	stdio[STDIN_FILENO] = stdin;
	return SUCCESS;
}

void restore_stdio(int stdio[2])
{
	dup2(stdio[STDOUT_FILENO], STDOUT_FILENO);
	dup2(stdio[STDIN_FILENO], STDIN_FILENO);
	close(stdio[STDOUT_FILENO]);
	close(stdio[STDIN_FILENO]);
}
