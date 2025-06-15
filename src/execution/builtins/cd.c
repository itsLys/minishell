/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:49:52 by ihajji            #+#    #+#             */
/*   Updated: 2025/06/13 16:09:46 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

// WARN: use stderr;

char *get_dir(char **argv, char *home)
{
	if (argv[1] == NULL || ft_strcmp(argv[1], "~") == 0)
	{
		if (home == NULL)
			return printf("%s: %s\n", argv[0], "HOME not set"), NULL;
		return home;
	}
	else if (ft_strncmp(argv[1], "~/", 2) == 0)
	{
		if (home == NULL)
			return printf("%s: %s\n", argv[0], "HOME not set"), NULL;
		return ft_strjoin(home, ft_strchr(argv[1], '/') + 1);
	}
	else
		return ft_strdup(argv[1]);
}

int	cd(char **argv, t_env **env)
{
	char	*dir;
	char	*home;
	t_env	*home_var;

	home_var = env_find_var(*env, "HOME");
	if (home_var)
		home = ft_strjoin(home_var->value, "/");
	else
		home = NULL;
	if (argv[1] && argv[2])
		return printf("%s: %s\n", argv[0], "too many arguments"), FAILIURE;
	else
		dir = get_dir(argv, home);
	if (dir)
	{
		if (dir[0] == '\0')
			return SUCCESS;
		if (chdir(dir) != SUCCESS)
			return free(dir), perror(argv[0]), FAILIURE; // check errno and print accordingly, I guess
	}
	return FAILIURE;
}
// TODO: implement error messages close to bash
// use av[0] instead of the bare name
// use dprintf instead of pf
