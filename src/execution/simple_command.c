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
		{
			ft_execvpe(argv[0], argv, make_envp(data->env));
			exit(CMD_NOT_FOUND); // clean exit
		}
		else if (pid == ERROR)
			perror("fork"); // clean exit
	}
	waitpid(pid, &status, 0);
	return status;
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
		return WEXITSTATUS(execute_bin(argv, data, run_in_shell));
}
