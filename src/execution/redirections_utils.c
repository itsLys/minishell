/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 18:38:36 by ihajji            #+#    #+#             */
/*   Updated: 2025/07/02 18:38:36 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int save_stdio(int stdio[2], t_data *data)
{
	int	s_stdin;
	int	s_stdout;

	s_stdout = dup(STDOUT_FILENO);
	s_stdin = dup(STDIN_FILENO);
	if (s_stdout == ERROR || s_stdin == ERROR)
		return perror("dup"), clean_exit(FAILIURE, data), FAILIURE;
	stdio[STDOUT_FILENO] =  s_stdout;
	stdio[STDIN_FILENO] = s_stdin;
	return SUCCESS;
}

void restore_stdio(int stdio[2])
{
	dup2(stdio[STDOUT_FILENO], STDOUT_FILENO);
	dup2(stdio[STDIN_FILENO], STDIN_FILENO);
	close(stdio[STDOUT_FILENO]);
	close(stdio[STDIN_FILENO]);
}
