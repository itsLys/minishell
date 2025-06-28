#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

volatile sig_atomic_t g_interrupted = 0;

void sigint_handler(int sig)
{
	(void)sig;
	g_interrupted = 1;
	rl_replace_line("", 0);
	rl_done = 1;
	write(STDOUT_FILENO, "\n", 1);
}

void setup_signals(void)
{
	struct sigaction sa;
	sa.sa_handler = sigint_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
}

int main(void)
{
	int     fd;
	char    *line;
	char    *limiter = "EOF";

	// ouvrir fichier temporaire
	fd = open("/tmp/heredoc_test.tmp", O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd == -1)
	{
		perror("open");
		return 1;
	}

	// setup signal handler
	signal(SIGINT, sigint_handler);
	rl_catch_signals = 0;

	while (1)
	{
		line = readline("> ");
		if (!line || g_interrupted)
			break;

		if (strcmp(line, limiter) == 0)
		{
			free(line);
			break;
		}

		write(fd, line, strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);

	// Lire le contenu
	fd = open("/tmp/heredoc_test.tmp", O_RDONLY);
	if (fd == -1)
	{
		perror("open read");
		return 1;
	}

	write(STDOUT_FILENO, "\nContenu du heredoc:\n", 22);
	char buffer[1024];
	ssize_t bytes;
	while ((bytes = read(fd, buffer, sizeof(buffer))) > 0)
		write(STDOUT_FILENO, buffer, bytes);
	close(fd);
	unlink("/tmp/heredoc_test.tmp");

	return 0;
}
