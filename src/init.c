/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:37:26 by ihajji            #+#    #+#             */
/*   Updated: 2025/06/21 16:05:59 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include <signals.h>

void init_default_var(t_data *data, t_env **env)
{
	t_env	*pwd;
	
	pwd = env_find_var(*env, "PWD");
	if (pwd)
		env_remove_node(pwd, env);
	env_add_last(new_env_node(ft_strdup("PWD"), ft_strdup(data->pwd), true), env);
	if (env_find_var(*env, "OLDPWD") == NULL)
		env_add_last(new_env_node(ft_strdup("OLDPWD"), NULL, true), env);
	else
		env_remove_node(env_find_var(*env, "OLDPWD"), env);
}

int init_minishell(char **env, t_data *data)
{
	setup_signals();
	rl_outstream = stderr;
	data->env = dup_env(env);
	data->pwd = getcwd(NULL, 0);
	if (data->pwd == NULL)
		perror("malloc"); // exit clean
	init_default_var(data, &(data->env));
	return SUCCESS;
}
