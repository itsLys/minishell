/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading_stdin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 20:54:02 by zbengued          #+#    #+#             */
/*   Updated: 2025/06/25 21:18:28 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_string.h>
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
	char	suffix[16];
	t_str	filename;
	int		fd_random;

	str_create(&filename, "/tmp/");
	fd_random = open("/dev/random", O_RDONLY);
	str_create(&prefix, "heredoc_");
	read(fd_random, suffix, 15);
	close(fd_random);
	suffix[15] = '\0';
	str_append(&prefix, suffix);
	str_append(&filename, prefix.data);
	return (filename);
}

static int my_rl_event_hook(void)
{
    if (g_interrupted)
        rl_done = 1;
    return 0;
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

int	run_heredoc(char *delim, char *filename)
{
	int		fd_hered;
	pid_t	pid;
	int		status;

	fd_hered = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd_hered == -1)
		return -1;
	pid = fork();
	if (pid == -1)
		return -1;
	if (pid == 0)
		read_until_sigint_or_delim(fd_hered, delim);
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	close(fd_hered);
	return (*(int *)ternary(WIFSIGNALED(status), &(int){-1}, &(int){0}));
}
//
// int	main(void)
// {
// 	int		fd;
// 	char	buffer[1024];
// 	ssize_t	bytes;
//
// 	t_str	tmp_file = generate_file_name();
// 	printf("filename = %s\n", tmp_file.data);
// 	if (run_heredoc("EOF", tmp_file.data) == -1)
// 	{
// 		write(STDOUT_FILENO, "heredoc aborted\n", 16);
// 		return 1;
// 	}
// 	// Lecture du contenu du fichier temporaire
// 	fd = open(tmp_file.data, O_RDONLY);
// 	if (fd == -1)
// 		return perror("open"), 1;
//
// 	write(STDOUT_FILENO, "Contenu du heredoc:\n", 21);
// 	while ((bytes = read(fd, buffer, sizeof(buffer))) > 0)
// 		write(STDOUT_FILENO, buffer, bytes);
// 	close(fd);
// 	unlink(tmp_file.data); // Supprime le fichier temporaire
// 	return 0;
// }
//
// int main(void)
// {
// 	char *line;
//
// 	rl_catch_signals = 0;
// 	while (1)
// 	{
// 		line = readline("> ");
// 		if (!line || g_interrupted)
// 			break;
// 		printf("input: %s\n", line);
// 		free(line);
// 	}
// 	printf("Exited\n");
// }
