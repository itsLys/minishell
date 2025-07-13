/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getoutput.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 11:05:43 by ihajji            #+#    #+#             */
/*   Updated: 2025/07/13 12:28:29 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"
#include <sys/wait.h>
#include <linux/limits.h>

#define CHILD_PROC 0

// static int save_stdio(int stdio[2])
// {
// 	int	s_stdin;
// 	int	s_stdout;
//
// 	s_stdout = dup(STDOUT_FILENO);
// 	s_stdin = dup(STDIN_FILENO);
// 	if (s_stdout == ERROR || s_stdin == ERROR)
// 		return FAILIURE;
// 	stdio[STDOUT_FILENO] =  s_stdout;
// 	stdio[STDIN_FILENO] = s_stdin;
// 	return SUCCESS;
// }
//
// static void restore_stdio(int stdio[2])
// {
// 	dup2(stdio[STDOUT_FILENO], STDOUT_FILENO);
// 	dup2(stdio[STDIN_FILENO], STDIN_FILENO);
// 	close(stdio[STDOUT_FILENO]);
// 	close(stdio[STDIN_FILENO]);
// }

#include <stdio.h>
char	*ft_getoutput(char **argv, char **envp)
{
	pid_t	pid;
	int		pipefd[2];
	char	*output;
	int		bytes_read;
	// char	**argv;
	int		status;
	// int		stdio[2];

	if (pipe(pipefd) == ERROR)
		return NULL;
	pid = fork();
	// argv = ft_tokenize(cmd);
	// while (argv)
	// 	printf("token: %s\n", *(argv++));
	// exit(31);
	// if (argv == NULL)
	// 	return NULL;
	// if (save_stdio(stdio) == ERROR)
	// 	return NULL;
	if (pid == CHILD_PROC)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		close(pipefd[0]);
		close(STDERR_FILENO);
		status = ft_execvpe(argv[0], argv, envp);
		// ft_free_vector(argv);
		exit(status);
	}
	else if (pid == ERROR)
		return /* restore_stdio(stdio), */ NULL;
	waitpid(pid, &status, 0);
	// restore_stdio(stdio);
	if (WEXITSTATUS(status) != 0)
		return /* restore_stdio(stdio), */ NULL;
	output = malloc(PIPE_BUF + 1);
	if (output == NULL)
		return /* restore_stdio(stdio), */ NULL;
	bytes_read = read(pipefd[0], output, PIPE_BUF);
	if (bytes_read == ERROR)
		return /* restore_stdio(stdio), */ free(output), NULL;
	if (output[bytes_read - 1] ==  '\n')
		output[bytes_read - 1] = 0;
	else
		output[bytes_read] = 0;
	return (/* restore_stdio(stdio), */ output);
}
