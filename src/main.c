/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 15:02:11 by ihajji            #+#    #+#             */
/*   Updated: 2025/07/13 12:38:01 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include "execution.h"
#include <signals.h>
#include <linux/limits.h>

// t_data *g_data(void)
// {
// 	static t_data data;
// 	return &data;
// }

const char	*get_status_color(void)
{
	if (g_interrupted[2] == 0)
		return COLOR_GREEN;
	return COLOR_RED;
}

char *get_branch(void)
{
	char	*branch;

	branch = ft_getoutput((char *[]){"git","rev-parse", "--abbrev-ref", "HEAD", NULL}, __environ);
	if (branch == NULL)
		return ft_strdup("~");
	return branch;
}

char *get_time(void)
{
	char *time;

	time = ft_getoutput((char *[]){"date","+%a %d %H:%M", NULL}, __environ);
	return time;
}

char	*build_prompt(t_data *data)
{
	static char	prompt[PATH_MAX];
	char		*user;
	// char		time[16];
	char		*time;
	char		*branch;

	user = get_env_value(data->env, "USER").data;
	if (user == NULL)
		user = ft_strdup("annonymos");
	// if (ft_strlen(pwd) == get_env_value(data->env, "HOME").size) // WARN: FLAWED
	// 	pwd = "~";
	// get_rtc_time(time, 16);
	// time = ft_getoutput((char *[]){"date","+%a %d %H:%M", NULL}, __environ);
	branch = get_branch();
	time = get_time();
	// if (g_interrupted[2] == 0)
	ft_snprintf(prompt, sizeof(prompt),
			// "┏[" COLOR_GREEN "%d" COLOR_RESET "]"
			"┏[" "%s" "%d" COLOR_RESET "]"
			"-(" COLOR_BLUE "%s" COLOR_RESET ")"
			// "-(" COLOR_MAGENTA "%s" COLOR_RESET ")"
			"-(" COLOR_RED "%s" COLOR_RESET ")\n"
			"┗━━━(" COLOR_CYAN "%s" COLOR_RESET ")"
			"-(" COLOR_MAGENTA "%s" COLOR_RESET ")-> ",
			get_status_color(), g_interrupted[2], user, time, data->pwd, branch);
	free(branch);
	free(time);
	free(user);
	// free(pwd);
	return (prompt);
}

static int	get_input(t_data *data)
{
	if (isatty(fileno(stdin)))
		data->input = readline(build_prompt(data));
	else
	{
		char *line;
		line = get_next_line(fileno(stdin));
		data->input = ft_strtrim(line, "\n");
		free(line);
	} // NOTE: FOR TESTER, REMOVE LATER

	// data->input = readline(build_prompt(data));
	if (!data->input)
	{
		// printf("before exiting\n");
		clean_exit(g_interrupted[2], data);
		return 1;
		// return printf("exit\n");
	}
	return (SUCCESS);
}


// BUG: /bin/echo $"42$"
//			ms:	42 |	bash:	42$
// BUG: /bin/echo $USER'$USER'text oui oui     oui  oui $USER oui      $USER ''
//			bash:	|ihajji$USERtext oui oui oui oui ihajji oui ihajji $
//			ms		|ihajji$USERtext oui oui oui oui ihajji oui ihajji$
// BUG: /bin/echo '' ""
// 			bash:	| $
// 			ms:		|$		#ghaytfixa fach tfixi li fo9o
// BUG:	/bin/echo $USER$TESTNOTFOUND$HOME$ | cat -e
//			ms:		|ihajji$HOME$$
//			bahs:	|ihajji/home/ihajji$$
// BUG:	echo "" "" "" -n -n -n -n
// 			argv makiwslnich fih strings li khawying
// 			expecting:
// 				0:      |echo|
// 				1:      |   -n|
// 				2:      |-n|
// 				3:      |-n|
// 				4:      |-n|
// 			recieving:
// 				0:      |echo|
// 				1:      |-n|
// 				2:      |-n|
// 				3:      |-n|
// 				4:      |-n|


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
		// ast_print(data.ast, 0, "", 1);
		free_resources(data.input, &data.tokens, &data.ast);
	}
}
