/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_actions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:39:09 by ihajji            #+#    #+#             */
/*   Updated: 2025/06/21 15:58:47 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

t_env	*env_find_var(t_env *env, char *name)
{
	if (env == NULL || name == NULL)
		return (NULL);
	while (env)
	{
		if (ft_strcmp(env->name, name) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

t_env	*new_env_node(char *name, char *value, bool exported)
{
	t_env	*new;

	if (name == NULL)  // I can accept a NULL value, but not a null name
		return (NULL); // NOTE: exit_clean on return (address);
	new = ft_calloc(sizeof(t_env), 1);
	if (new == NULL)
		return (NULL); // NOTE: exit_clean on return address
	new->name = name;
	new->value = value;
	new->exported = exported;
	new->next = NULL;
	return (new);
}

void	env_add_last(t_env *node, t_env **env)
{
	t_env	*tmp;

	if (env == NULL)
		return ; // silenty fail
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

void	env_remove_node(t_env *node, t_env **env)
{
	t_env	*tmp;

	tmp = *env;
	if (tmp == NULL)
		return ;
	while (tmp->next && tmp->next != node)
		tmp = tmp->next;
	if (tmp->next)
	{
		tmp->next = node->next;
		free_env_node(node);
	}
}
