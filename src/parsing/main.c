/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 15:02:11 by ihajji            #+#    #+#             */
/*   Updated: 2025/04/25 19:05:44 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

char	*build_prompt(void)
{
	static char	prompt[PATH_MAX];
	char		cwd[PATH_MAX];

	prompt[0] = '\0';
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (NULL);
	ft_strlcat(prompt, COLOR_BLUE, sizeof(prompt));
	ft_strlcat(prompt, cwd, sizeof(prompt));
	ft_strlcat(prompt, COLOR_RESET, sizeof(prompt));
	ft_strlcat(prompt, " minishell$ ", sizeof(prompt));
	return (prompt);
}

int	main(int ac __attribute__((unused)), char **av __attribute__((unused)),
		char **env)
{
	char	*line;
	t_token	*tokens;
	t_ast_node	*node;

	tokens = NULL;
	(void)env;
	while (1)
	{
		line = readline(build_prompt());
		if (!line)
		{
			printf("exit\n");
			free(line);
			break ;
		}
		lexer(&tokens, line);
		node = compound_command(&tokens);
		if (*line)
			add_history(line);
		//print_tokens(tokens);
		ast_print(node, 0, "", 1);
		free_tokens(&tokens);
		free(line);
	}
}
