/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 09:15:21 by ihajji            #+#    #+#             */
/*   Updated: 2025/06/26 13:05:21 by ihajji           ###   ########.fr       */
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

int	execute_simple_command(t_ast_node *node, t_data *data, bool run_in_shell)
{
	char		**argv;
	t_builtin	*builtin;
	int			std_io[2];
	int			status;


	argv = extract_args(&node->child->args, data->env);
	if (argv && *argv == NULL)
		return 0;
	// argv = str_arr_to_cstr_array(&node->child->args);
	std_io[STDOUT_FILENO] = dup(STDOUT_FILENO);
	std_io[STDIN_FILENO] = dup(STDIN_FILENO);
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
	dup2(std_io[STDOUT_FILENO], STDOUT_FILENO);
	dup2(std_io[STDIN_FILENO], STDIN_FILENO);
	close(std_io[STDOUT_FILENO]);
	close(std_io[STDIN_FILENO]);
	return status;
}
