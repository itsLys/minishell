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

void init_default_var(t_data *data, t_env **env)
{
	env_add_last(new_env_node(ft_strdup("PWD"), ft_strdup(data->pwd), true), env);
	if (env_find_var(*env, "OLDPWD") == NULL)
		env_add_last(new_env_node(ft_strdup("OLDPWD"), NULL, true), env);
	else
		env_remove_node(env_find_var(*env, "OLDPWD"), env);
	// if (env_find_var(*env, "SHLVL"))
	// SHLVL
	// _ var, when giving a fresh environment to a subprocess
}

int init_minishell(char **env, t_data *data)
{
	data->env = dup_env(env);
	data->pwd = getcwd(NULL, 0);
	if (data->pwd == NULL)
		perror("malloc"); // exit clean
	init_default_var(data, &(data->env));
	return SUCCESS;
}
