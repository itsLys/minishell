/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:49:52 by ihajji            #+#    #+#             */
/*   Updated: 2025/06/21 16:28:33 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static char	*get_dir(char **argv, char *home)
{
	if (argv[1] == NULL || ft_strcmp(argv[1], "~") == 0)
	{
		if (home == NULL)
			return (print_error(argv[0], "HOME not set"), NULL);
		return (ft_strdup(home));
	}
	else if (ft_strncmp(argv[1], "~/", 2) == 0)
	{
		if (home == NULL)
			return (print_error(argv[0], "HOME not set"), NULL);
		return (ft_strjoin(home, ft_strchr(argv[1], '/') + 1));
	}
	else
		return (ft_strdup(argv[1]));
}

static void update_pwd(char *cwd, t_data *data, t_env *env)
{
	t_env *old;
	t_env *pwd;

	if (cwd == NULL)
		perror("getcwd"); // clean exit
	old = env_find_var(env, "OLDPWD");
	pwd = env_find_var(env, "PWD");
	if (old && pwd)
	{
		free(old->value);
		old->value = data->pwd; 
		free(data->oldpwd);
		data->oldpwd = ft_strdup(old->value);
	}
	if (pwd && cwd)
	{
		free(pwd->value);
		pwd->value = cwd;
		free(data->pwd);
		data->pwd = ft_strdup(cwd);
	}

}

int	cd(char **argv, t_env **env, t_data *data)
{
	char	*dir;
	char	*home;
	t_env	*home_var;

	dir = NULL;
	if (argv[1] && argv[2])
		return (print_error(argv[0], "too many arguments"), FAILIURE);
	home_var = env_find_var(*env, "HOME");
	if (home_var)
		home = ft_strjoin(home_var->value, "/");
	else
		home = NULL;
	dir = get_dir(argv, home);
	free(home);
	if (dir)
	{
		if (dir[0] == '\0')
			return (free(dir), SUCCESS);
		if (chdir(dir) != SUCCESS)
			return (free(dir), perror(argv[0]), FAILIURE);
		update_pwd(getcwd(NULL, 0), data, *env);
		return free(dir), SUCCESS;
	}
	return (FAILIURE);
}
// check errno and print accordingly, I guess
// TODO: implement error messages close to bash
// use av[0] instead of the bare name
// use dprintf instead of pf
