/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 15:02:11 by ihajji            #+#    #+#             */
/*   Updated: 2025/07/08 00:53:48 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include "execution.h"
#include <signals.h>

// t_data *g_data(void)
// {
// 	static t_data data;
// 	return &data;
// }

char	*build_prompt(t_data *data)
{
	static char	prompt[PATH_MAX];
	char		*user;
	char		*pwd;
	char		time[16];

	user = get_env_value(data->env, "USER").data;
	pwd = get_env_value(data->env, "PWD").data;
	get_rtc_time(time, 16);
    ft_snprintf(prompt, sizeof(prompt),
        "┏[%s : %d]-(%s)-(%s)-(%s)\n"
        "┗━━━(%s)-> ",
        "ζ", g_interrupted[2], user, "minishell", time, pwd);
	return (prompt);
}
// BUG: prompt and pwd fails if `mkdir -p x/y/z and cd x/y/z, and then rm -rf ../../../x`

static int	get_input(t_data *data)
{
	data->input = readline(build_prompt(data));
	if (!data->input)
	{
		free_resources(data->input, &data->tokens, &data->ast);
		return printf("exit\n");
	}
	return (SUCCESS);
}


// void free_data(t_data *data)
// {
// 	free_env(data->env);
// 	free(data->input);
// 	free(data->oldpwd);
// 	free(data->pwd);
// }
//
// void	clean_exit(unsigned int status, t_data *data)
// {
// 	ast_free(data->ast);
// 	free_tokens(&(data->tokens));
// 	free_data(data);
// 	exit(status);
// }

int	main(int ac __attribute__((unused)), char **av __attribute__((unused)),
		char **env)
{
	// t_token			*tokens;
	// t_ast_node		*node;
	// t_data			*data;
	// int				status;
	static t_data	data;

	// status = 0;
	// data = g_data(); // change to init data later, allocates to it
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
		printf("status	%d\n", g_interrupted[2]);
		ast_print(data.ast, 0, "", 1);
		free_resources(data.input, &data.tokens, &data.ast);
	}
}
