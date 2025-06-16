/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:37:26 by ihajji            #+#    #+#             */
/*   Updated: 2025/06/12 00:16:45 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

// t_env *new_env(char *name, char *value, bool is_exported)
// {
// 	t_env *new;
//
// 	new = ft_calloc(sizeof(t_env), 1);
// 	if (new == NULL)
// 		return NULL; // exit_clean  on return address
// 	new->name = name;
// 	new->value = value;
// 	if (!new->name)
// 		return NULL; // clean exit
// 	new->is_exported = is_exported;
// 	new->next = NULL;
// 	return new;
// }

// static t_env *init_env_copy(char **env)
// {
// 	t_env *env_copy;
// 	t_env *new;
// 	char *eq_sign;
// 	int i;
//
// 	i = 0;
// 	env_copy = NULL;
// 	while (env[i])
// 	{
// 		eq_sign = ft_strchr(env[i], '=');
// 		if (!eq_sign && ++i)
// 			continue ;
// 		new = new_env(ft_strndup(env[i], eq_sign - env[i]), ft_strdup(eq_sign + 1), TRUE);
// 		if (new == NULL)
// 			return free_env_copy(env_copy); // exit_clean
// 		new->next = env_copy;
// 		env_copy = new;
// 		i++;
// 	}
// 	return env_copy;
// }

// void add_env_var(char *name, char *value, int is_exported)
// {
// 	t_data *data;
// 	t_env *new;
//
// 	data = g_data();
// 	new = new_env(name, value, is_exported);
// 	new->next = data->env_copy;
// 	data->env_copy = new;
// }

void init_default_var(t_env **env)
{
	env_add_last(new_env_node(ft_strdup("PWD"), NULL, true), env);
	if (env_find_var(*env, "OLDPWD") == NULL)
		env_add_last(new_env_node(ft_strdup("OLDPWD"), NULL, true), env);
	// SHLVL
	// _ var, when giving a fresh environment to a subprocess
}

int init_minishell(char **env, t_data *data)
{
	data->env = dup_env(env);
	init_default_var(&(data->env));
	// data->builtins = init_builtins(); // TODO: Move to a sutable place; initialization perhaps
	return SUCCESS;
}
// NOTE: use the library boolean instead of yours
//
