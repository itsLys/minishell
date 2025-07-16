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

char	*strip_home_prefix(char *pwd, t_data *data)
{
	char	*prefix;
	t_str	user;
	size_t	len;

	user = get_env_value(data->env, "USER");
	prefix = ft_strjoin("/home/", user.data);
	len = ft_strlen(prefix);
	if (ft_strncmp(pwd, prefix, len) == 0)
	{
		if (pwd[len] == '\0')
			return (str_destroy(&user), free(prefix), "~");
		return (str_destroy(&user), free(prefix), pwd + len);
	}
	str_destroy(&user);
	free(prefix);
	return (pwd);
}

char	*build_prompt(t_data *data)
{
	static char	prompt[PATH_MAX];
	char		*user;
	char		*time;
	char		*branch;
	char		*status;

	ft_memset(prompt, 0, PATH_MAX);
	user = get_env_value(data->env, "USER").data;
	if (user[0] == '\0')
		user = ft_strdup("annonymos");
	branch = get_branch();
	time = get_time();
	status = ft_itoa(g_interrupted[2]);
	build_first_line(prompt, status, user, time);
	build_second_line(prompt, strip_home_prefix(data->pwd, data), branch);
	free(status);
	free(branch);
	free(time);
	free(user);
	return (prompt);
}

// BUG: unset PWD && cd / && echo $PWD : should reset PWD and print it !
// leak on :
// ==1827889== 34 bytes in 4 blocks are definitely lost in loss record 15 of 81
// ==1827889==    at 0x484DCD3: realloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
// ==1827889==    by 0x49DA7BC: getcwd (getcwd.c:86)
// ==1827889==    by 0x4032F1: cd (cd.c:80)
// ==1827889==    by 0x402EAC: execute_simple_command (simple_command.c:74)
// ==1827889==    by 0x401DFC: execute (main.c:26)
// ==1827889==    by 0x401DD2: execute (main.c:24)
// ==1827889==    by 0x4028C9: execute_pipeline (pipeline.c:91)
// ==1827889==    by 0x401DA4: execute (main.c:22)
// ==1827889==    by 0x402C8E: execute_compound (compound_command.c:46)
// ==1827889==    by 0x401D82: execute (main.c:20)
// ==1827889==    by 0x4015C3: main (main.c:96)

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
