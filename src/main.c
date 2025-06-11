/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 15:02:11 by ihajji            #+#    #+#             */
/*   Updated: 2025/06/11 17:13:43 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include "execution.h"

t_data	g_data;

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

int	get_input(void)
{
	g_data.input = readline(build_prompt());
	if (!g_data.input)
	{
		free(g_data.input);
		return (printf("exit\n"));
	}
	return (SUCCESS);
}

void	free_resources(char *input, t_token **tokens, t_ast_node **node)
{
	free_tokens(tokens);
	if (*node)
	{
		ast_free(*node);
		*node = NULL;
	}
	free(input);
}

int	main(int ac __attribute__((unused)), char **av __attribute__((unused)),
		char **env)
{
	t_token		*tokens;
	t_ast_node	*node;

	tokens = NULL;
	node = NULL;
	(void)env;
	while (1)
	{
		if (get_input())
			return (SUCCESS);
		parse_input(g_data.input, &tokens, &node);
		if (node)
			execute(node);
		ast_print(node, 0, "", 1);
		free_resources(g_data.input, &tokens, &node);
	}
}
