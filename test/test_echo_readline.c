#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int main(void) {
	rl_outstream = stderr; // ← clé ici
	char *line = readline("prompt> ");
	printf("You typed: %s\n", line);
}
