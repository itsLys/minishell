/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 09:15:21 by ihajji            #+#    #+#             */
/*   Updated: 2025/07/13 12:56:21 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "signals.h"

static void	print_exec_error(int status, char *cmd)
{
	if (status == NON_EXEC)
		ft_dprintf(STDERR, "%s: cannot execute\n", cmd);
	else
		ft_dprintf(STDERR, "%s: command not found\n", cmd);
}

static int	execute_bin(char **argv, t_data *data)
{
	int			status;
	char		**envp;

	envp = make_envp(data->env);
	if (envp == NULL)
		clean_exit(FAILIURE, data);
	signal(SIGQUIT, SIG_DFL);
	status = ft_execvpe(argv[0], argv, envp);
	print_exec_error(status, argv[0]);
	ft_free_vector(argv);
	ft_free_vector(envp);
	clean_exit(status, data);
	return (status);
}

static int	execute_process(char **argv, bool run_in_shell, t_data *data)
{
	pid_t	pid;
	int		status;

	if (run_in_shell)
		execute_bin(argv, data);
	pid = fork();
	if (pid == 0)
		execute_bin(argv, data);
	else if (pid == ERROR)
		return (perror("fork"), clean_exit(FAILIURE, data), FAILIURE);
	waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
}

int	execute_simple_command(t_ast_node *node, t_data *data, bool run_in_shell)
{
	char		**argv;
	t_builtin	*builtin;
	int			stdio[2];
	int			status;

	status = 0;
	save_stdio(stdio, data);
	if (node->child->sibling->child
		&& setup_redir(node->child->sibling->child, data))
		return (restore_stdio(stdio), FAILIURE);
	argv = extract_args(&node->child->args, data->env);
	if (argv && *argv == NULL)
		return (restore_stdio(stdio), ft_free_vector(argv), SUCCESS);
	builtin = find_builtin(argv[0]);
	if (builtin)
		status = builtin->function(argv, &(data->env), data);
	else
		status = execute_process(argv, run_in_shell, data);
	restore_stdio(stdio);
	ft_free_vector(argv);
	g_interrupted[2] = status;
	return (status);
}
