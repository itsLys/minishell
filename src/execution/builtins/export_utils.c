/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 15:04:38 by ihajji            #+#    #+#             */
/*   Updated: 2025/07/13 12:45:56 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

bool	is_valid(char *arg, t_mode *mode)
{
	int	i;

	i = 1;
	if (arg[0] != '_' && ft_isalpha(arg[0]) == false)
		return (false);
	while (arg[i] && (ft_isalnum(arg[i]) || arg[i] == '_'))
		i++;
	if (arg[i] == 0)
	{
		*mode = EXPORT;
		return (true);
	}
	if (arg[i] == '+' && arg[i + 1] == '=')
	{
		*mode = CONCAT;
		return (true);
	}
	if (arg[i] == '=')
	{
		*mode = ASSIGN;
		return (true);
	}
	return (false);
}

void	export_var(char *arg, t_env **env)
{
	t_env	*node;

	node = *env;
	while (node)
	{
		if (ft_strcmp(arg, node->name) == 0)
		{
			node->exported = true;
			return ;
		}
		node = node->next;
	}
	env_add_last(new_env_node(ft_strdup(arg), NULL, true), env);
}

void	concat_var(char *arg, t_env **env)
{
	t_env	*node;
	char	*new_val;
	char	*tmp;
	char	*plus;

	plus = ft_strchr(arg, '+');
	node = *env;
	new_val = ft_strdup(plus + 2);
	while (node)
	{
		if (ft_strncmp(arg, node->name, ft_strlen(node->name)) == 0 && arg
			+ ft_strlen(node->name) == plus)
		{
			tmp = node->value;
			node->value = ft_strjoin(node->value, new_val);
			node->exported = true;
			free(tmp);
			free(new_val);
			return ;
		}
		node = node->next;
	}
	free(new_val);
	env_add_last(new_env_node(ft_strndup(arg, plus - arg), ft_strdup(plus + 2),
			true), env);
}

void	assign_var(char *arg, t_env **env)
{
	t_env	*node;
	char	*tmp;
	char	*eq;

	eq = ft_strchr(arg, '=');
	node = *env;
	while (node)
	{
		if (ft_strncmp(arg, node->name, ft_strlen(node->name)) == 0 && arg
			+ ft_strlen(node->name) == eq)
		{
			tmp = node->value;
			node->value = ft_strdup(eq + 1);
			node->exported = true;
			free(tmp);
			return ;
		}
		node = node->next;
	}
	env_add_last(new_env_node(ft_strndup(arg, eq - arg), ft_strdup(eq + 1),
			true), env);
}

t_env	*dup_env_sorted(t_env *env)
{
	t_env	*tmp;
	t_env	*node;

	tmp = NULL;
	node = env;
	while (node)
	{
		if (node->value)
			env_add_last(new_env_node(ft_strdup(node->name),
					ft_strdup(node->value),
					true),
				&tmp);
		else
			env_add_last(new_env_node(ft_strdup(node->name), NULL, true), &tmp);
		node = node->next;
	}
	sort_env(&tmp);
	return (tmp);
}
