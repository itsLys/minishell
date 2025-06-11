#include "minishell.h"

void	print_env(t_env *env)
{
	printf("\n\n::::::::ENVIRONMENT COPY:::::::\n\n");
	printf("| NAME		| VALUE		| EXPORTED?\n");
	while (env)
	{
		printf("| %s		| %s	| %d\n", env->name, env->value, env->is_exported);
		env = env->next;
	}
}
