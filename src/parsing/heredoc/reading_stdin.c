/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading_stdin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 20:54:02 by zbengued          #+#    #+#             */
/*   Updated: 2025/06/29 12:44:14 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_string.h>
#include <execution.h>
#include <parsing.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <fcntl.h>
#include <signal.h>

int	g_interrupted = 0;

static void	sigint_handler(int sig)
{
	(void)sig;
	g_interrupted = 1;
	ft_dprintf(STDOUT_FILENO, "\n");
}

// NOTE : heredoc876yuhjgtr0p9uj
t_str	generate_file_name(void)
{
	t_str	prefix;
	t_str	suffix;
	char 	buff[10];
	t_str	filename;
	int		fd_random;

	str_create(&filename, "/tmp/");
	fd_random = open("/dev/random", O_RDONLY);
	str_create(&prefix, "heredoc_");
	read(fd_random, buff, 9);
	buff[9] = '\0';
	close(fd_random);
	str_create(&suffix, buff);
	str_replace(&suffix, "\\", "6", ALL);
	str_append(&prefix, suffix.data);
	str_append(&filename, prefix.data);
	return (filename);
}

static int my_rl_event_hook(void)
{
    if (g_interrupted)
        rl_done = 1;
    return (0);
}
static void	read_until_sigint_or_delim(int fd_hered, char *delim)
{	
	char	*line;
	rl_catch_signals = 0;
	rl_catch_sigwinch = 0;
	rl_event_hook = my_rl_event_hook;
	signal(SIGINT, sigint_handler);
	while (true)
	{
		line = readline("> ");
		if (!line || g_interrupted)
			break;
		if (!ft_strcmp(line, delim))
		{
			free(line);
			break;
		}
		ft_dprintf(fd_hered, "%s\n", line);
		free(line);
	}
	close(fd_hered);
	rl_catch_signals = 1;
	rl_catch_sigwinch = 1;
	rl_done = 0;
	exit(0);
}

int	run_heredoc(char *delim, t_str *filename)
{
	int		fd_hered;
	pid_t	pid;
	int		status;
	t_str	str_delim;
	t_str	mask;

	str_create(&str_delim, delim);
	mask = build_mask(&str_delim);
	if (!ft_strchr(delim, '\'') && !ft_strchr(delim, '"'))
		str_append(filename, "EXPAND");
	remove_quote(&str_delim, &mask);
	fd_hered = open(filename->data, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd_hered == -1)
		return -1;
	pid = fork();
	if (pid == -1)
		return -1;
	if (pid == 0)
		read_until_sigint_or_delim(fd_hered, str_delim.data);
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	close(fd_hered);
	return (*(int *)ternary(WIFSIGNALED(status), &(int){-1}, &(int){0}));
}
