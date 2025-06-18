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
// BUG: prompt and pwd fails if `mkdir -p x/y/z and cd x/y/z, and then rm -rf ../../../x`

static int	get_input(t_data *data)
{
	data->input = readline(build_prompt());
	if (!data->input)
	{
		free(data->input);
		return printf("exit\n");
	}
	return (SUCCESS);
}

int	main(int ac __attribute__((unused)), char **av __attribute__((unused)),
		char **env)
{
	t_token		*tokens;
	t_ast_node	*node;
	t_data *data;

	data = g_data(); // change to init data later, allocates to it
	init_minishell(env, data);
	tokens = NULL;
	node = NULL;
	while (1)
	{
		if (get_input(data))
			return (SUCCESS);
		parse_input(data->input, &tokens, &node);
		if (node)
			execute(node, data, false);
		ast_print(node, 0, "", 1);
		free_resources(data->input, &tokens, &node);
	}
}
