/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:39:09 by ihajji            #+#    #+#             */
/*   Updated: 2025/06/13 16:15:02 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
t_env *env_find_var(t_env *env, char *name)
{
	if (env == NULL || name == NULL)
		return NULL;
	while (env)
	{
		if (ft_strcmp(env->name, name) == 0)
			return (env);
		env = env->next;
	}
	return NULL;
}

t_env *new_env_node(char *name, char *value, bool exported)
{
	t_env	*new;

	if (name == NULL) // I can accept a NULL value, but not a null name
		return NULL; // NOTE: exit_clean on return address; 
	new = ft_calloc(sizeof(t_env), 1);
	if (new == NULL)
		return NULL; // NOTE: exit_clean on return address
	new->name = name;
	new->value = value;
	new->exported = exported;
	new->next = NULL;
	return new;
}

// void env_add_node(char *name, char *value, int is_exported)
// {
// 	t_data *data;
// 	t_env *new;
//
// 	data = g_data();
// 	new = new_env_var(name, value, is_exported);
// 	new->next = data->env_copy;
// 	data->env_copy = new;
// }

void env_add_last(t_env *node, t_env **env)
{
	t_env	*tmp;

	if (env == NULL)
		return; // silenty fail
	tmp = *env;
	if (tmp == NULL)
	{
		*env = node;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
}

t_env *dup_env(char **env)
{
	t_env	*env_dup;
	t_env	*node;
	char	*eq;
	int		i;

	i = 0;
	env_dup = NULL;
	while (env[i])
	{
		eq = ft_strchr(env[i], '=');
		if (!eq && ++i)
			continue ;
		node = new_env_node(ft_strndup(env[i], eq - env[i]), ft_strdup(eq + 1), true);
		if (node == NULL)
			return free_env_copy(env_dup); // NOTE: exit_clean
		env_add_last(node, &env_dup);
		i++;
	}
	return env_dup;
}

void sort_env(t_env **env)
{
	t_env tmp;
	t_env *j;
	t_env *i;

	i = *env;
	while (i)
	{
		j = i->next;
		while (j)
		{
			if (ft_strcmp(i->name, j->name) > 0)
			{
				tmp.name = i->name;
				i->name = j->name;
				j->name = tmp.name;
				tmp.value = i->value;
				i->value = j->value;
				j->value = tmp.value;
			}
			j = j->next;
		}
		i = i->next;
	}
}
