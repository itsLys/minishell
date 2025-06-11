/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 15:02:11 by ihajji            #+#    #+#             */
/*   Updated: 2025/06/10 16:43:14 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include "execution.h"

t_data *g_data(void)
{
	static t_data data;
	return &data;
}

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
	g_data()->input = readline(build_prompt());
	if (!g_data()->input)
	{
		free(g_data()->input);
		return printf("exit\n");
	}
	return (SUCCESS);

}

int	main(int ac __attribute__((unused)), char **av __attribute__((unused)),
		char **env)
{
	t_token		*tokens;
	t_ast_node	*node;

	init_minishell(env);
	tokens = NULL;
	node = NULL;
	while (1)
	{
		if (get_input())
			return (SUCCESS);
		parse_input(g_data()->input, &tokens, &node);
		if (node)
			execute(node);
		ast_print(node, 0, "", 1);
		free_resources(g_data()->input, &tokens, &node);
	}
}
