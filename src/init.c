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

#include "minishell.h"

static t_env *init_env_copy(char **env)
{
	t_env *env_copy;
	t_env *new;
	char *eq_sign;
	int i;

	i = 0;
	env_copy = NULL;
	while (env[i])
	{
		eq_sign = ft_strchr(env[i], '=');
		if (!eq_sign && ++i)
			continue ;
		new = ft_calloc(sizeof(t_env), 1);
		if (new == NULL)
			return free_env_copy(env_copy);
		new->name = ft_strndup(env[i], eq_sign - env[i]);
		new->value = ft_strdup(eq_sign + 1);
			if (!new->name || !new->value)
				return free_env_copy(env_copy);
		new->is_exported = TRUE;
		new->next = env_copy;
		env_copy = new;
		i++;
	}
	return env_copy;
}

int init_minishell(char **env)
{
	t_data *data;

	data = g_data();
	data->env_copy = init_env_copy(env);
	data->lwd = getcwd(NULL, 0);
	data->cwd = getcwd(NULL, 0);
	if (!data->lwd || !data->cwd || !data->env_copy)
		return ERROR; // exit cleanly, free everythng but make sure you're passing NULL to free();
	return SUCCESS;
}
