/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:39:09 by ihajji            #+#    #+#             */
/*   Updated: 2025/06/12 18:39:25 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

t_env *new_env(char *name, char *value, bool is_exported)
{
	t_env *new;

	new = ft_calloc(sizeof(t_env), 1);
	if (new == NULL)
		return NULL; // exit_clean  on return address
	new->name = name;
	new->value = value;
	if (!new->name)
		return NULL; // clean exit
	new->is_exported = is_exported;
	new->next = NULL;
	return new;
}

t_env *copy_env(char **env)
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
		new = new_env(ft_strndup(env[i], eq_sign - env[i]), ft_strdup(eq_sign + 1), TRUE);
		if (new == NULL)
			return free_env_copy(env_copy); // exit_clean
		new->next = env_copy;
		env_copy = new;
		i++;
	}
	return env_copy;
}

void add_env_var(char *name, char *value, int is_exported)
{
	t_data *data;
	t_env *new;

	data = g_data();
	new = new_env(name, value, is_exported);
	new->next = data->env_copy;
	data->env_copy = new;
}
