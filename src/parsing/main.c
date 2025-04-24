/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 15:02:11 by ihajji            #+#    #+#             */
/*   Updated: 2025/04/18 13:54:42 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
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
		if (*line)
			add_history(line);
		print_tokens(tokens);
		free_tokens(&tokens);
		free(line);
	}
}
