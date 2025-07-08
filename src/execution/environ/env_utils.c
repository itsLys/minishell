/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:39:09 by ihajji            #+#    #+#             */
/*   Updated: 2025/06/21 16:04:23 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

t_env	*dup_env(char **env)
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
		node = new_env_node(ft_strndup(env[i], eq - env[i]), ft_strdup(eq + 1),
				true);
		if (node == NULL)
			return (free_env(env_dup)); // NOTE: exit_clean
		env_add_last(node, &env_dup);
		i++;
	}
	return (env_dup);
}

void	sort_env(t_env **env)
{
	t_env	tmp;
	t_env	*j;
	t_env	*i;

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

void	free_env_node(t_env *node)
{
	// printf("free env node\n");
	free(node->name);
	free(node->value);
	free(node);
}
