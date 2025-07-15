/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 15:02:11 by ihajji            #+#    #+#             */
/*   Updated: 2025/07/14 19:54:36 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include "execution.h"

char	*build_prompt(t_data *data)
{
	static char	prompt[PATH_MAX];
	char		*user;
	char		*time;
	char		*branch;
	char		*status;

	ft_memset(prompt, 0, PATH_MAX);
	user = get_env_value(data->env, "USER").data;
	if (user == NULL)
		user = ft_strdup("annonymos");
	branch = get_branch();
	time = get_time();
	status = ft_itoa(g_interrupted[2]);
	build_first_line(prompt, status, user, time);
	build_second_line(prompt, data->pwd, branch);
	free(status);
	free(branch);
	free(time);
	free(user);
	return (prompt);
}

// WARN: change later this is only for test
static int	get_input(t_data *data)
{
	char	*line;

	if (isatty(fileno(stdin)))
		data->input = readline(build_prompt(data));
	else
	{
		line = get_next_line(fileno(stdin));
		data->input = ft_strtrim(line, "\n");
		free(line);
	}
	if (!data->input)
	{
		clean_exit(g_interrupted[2], data);
		return (1);
	}
	return (SUCCESS);
}

int	main(int ac __attribute__((unused)), char **av __attribute__((unused)),
		char **env)
{
	static t_data	data;

	init_minishell(env, &data);
	data.tokens = NULL;
	data.ast = NULL;
	while (1)
	{
		setup_signals();
		if (get_input(&data))
			return (SUCCESS);
		parse_input(data.input, &data.tokens, &data.ast);
		if (data.ast)
			g_interrupted[2] = execute(data.ast, &data, false);
		free_resources(data.input, &data.tokens, &data.ast);
	}
}
