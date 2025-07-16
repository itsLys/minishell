/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:49:52 by ihajji            #+#    #+#             */
/*   Updated: 2025/07/13 12:48:28 by ihajji           ###   ########.fr       */
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

static void	update_oldpwd(t_data *data, t_env **env)
{
	t_env	*oldpwd;

	oldpwd = env_find_var(*env, "OLDPWD");
	if (oldpwd == NULL)
	{
		oldpwd = new_env_node(ft_strdup("OLDPWD"), ft_strdup(data->pwd), true);
		env_add_last(oldpwd, env);
	}
	else
	{
		free(oldpwd->value);
		oldpwd->value = ft_strdup(data->pwd);
	}
	free(data->oldpwd);
	data->oldpwd = ft_strdup(data->pwd);
}

static void	update_pwd(char *cwd, t_data *data, t_env **env)
{
	t_env	*pwd;

	if (cwd == NULL)
	{
		perror("getcwd");
		clean_exit(FAILIURE, data);
	}
	update_oldpwd(data, env);
	pwd = env_find_var(*env, "PWD");
	if (pwd == NULL)
	{
		pwd = new_env_node(ft_strdup("PWD"), ft_strdup(cwd), true);
		env_add_last(pwd, env);
	}
	else
	{
		free(pwd->value);
		pwd->value = ft_strdup(cwd);
	}
	free(data->pwd);
	data->pwd = ft_strdup(cwd);
	free(cwd);
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
		update_pwd(getcwd(NULL, 0), data, env);
		return (free(dir), SUCCESS);
	}
	return (FAILIURE);
}
