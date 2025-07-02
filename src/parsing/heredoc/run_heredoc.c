/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 20:54:02 by zbengued          #+#    #+#             */
/*   Updated: 2025/07/01 12:27:13 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_string.h>
#include <execution.h>
#include <parsing.h>
#include <signals.h>

static void	sigint_handler_heredoc(int sig)
{
	(void)sig;
	g_interrupted[0] = 1;
	ft_dprintf(STDOUT_FILENO, "\n");
}

static int	my_rl_event_hook(void)
{
	if (g_interrupted[0])
		rl_done = 1;
	return (0);
}

static void	read_until_sigint_or_delim(int fd_hered, char *delim)
{
	char	*line;

	rl_event_hook = my_rl_event_hook;
	signal(SIGINT, sigint_handler_heredoc);
	while (true)
	{
		line = readline("> ");
		if (!line || g_interrupted[0])
			break ;
		if (!ft_strcmp(line, delim))
		{
			free(line);
			break ;
		}
		ft_dprintf(fd_hered, "%s\n", line);
		free(line);
	}
	close(fd_hered);
	exit(0);
}

static int	init_heredoc(t_str *filename, t_str *str_delim, char *delim)
{
	t_str	mask;
	int		fd_hered;

	str_create(str_delim, delim);
	mask = build_mask(str_delim);
	if (!ft_strchr(delim, '\'') && !ft_strchr(delim, '"'))
		str_append(filename, "EXPAND");
	remove_quote(str_delim);
	str_destroy(&mask);
	fd_hered = open(filename->data, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd_hered == -1)
		return (-1);
	return (fd_hered);
}

int	run_heredoc(char *delim, t_str *filename)
{
	int		fd_hered;
	pid_t	pid;
	int		status;
	t_str	str_delim;

	if (g_interrupted[0] == 1)
		return (-1);
	fd_hered = init_heredoc(filename, &str_delim, delim);
	if (fd_hered == -1)
		return (-1);
	signal(SIGINT, sigint_handler_heredoc);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
		read_until_sigint_or_delim(fd_hered, str_delim.data);
	waitpid(pid, &status, 0);
	signal(SIGINT, SIG_DFL);
	close(fd_hered);
	str_destroy(&str_delim);
	return (*(int *)ternary(WIFSIGNALED(status), &(int){0}, &(int){-1}));
}
