/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:56:36 by ihajji            #+#    #+#             */
/*   Updated: 2025/06/13 16:19:31 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

enum e_split
{
	NAME,
	VALUE
		// export V+=A
		// export V+=A
};

typedef enum e_mode
{
	CONCAT,
	ASSIGN,
	EXPORT
}
t_mode ;

bool is_valid(char *arg, t_mode *mode)
{
	int i;

	i = 1;
	if (ft_isalpha(arg[0]) == false)
		return false;
	while (arg[i] && ft_isalnum(arg[i]))
		i++;
	if (arg[i] == 0)
	{
		*mode = EXPORT;
		return true;
	}
	if (arg[i] == '+' && arg[i + 1] == '=')
	{
		*mode = CONCAT;
		return true;
	}
	if (arg[i] == '=')
	{
		*mode = ASSIGN;
		return true;
	}
	return false;
}

void	export_var(char *arg, t_env **env)
{
	t_env *node;

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

void concat_var(char *arg, t_env **env)
{
	t_env *node;
	char *new_val;
	char *tmp;
	char *plus;

	plus = ft_strchr(arg, '+');
	node = *env;
	new_val = ft_strdup(plus + 2);
	while (node)
	{
		if (ft_strncmp(arg, node->name, ft_strlen(node->name)) == 0
				&& arg + ft_strlen(node->name) == plus)
		{
			tmp = node->value;
			node->value = ft_strjoin(node->value, new_val);
			node->exported = true;
			free(tmp), free(new_val);
			return ;
		}
		node = node->next;
	}
	env_add_last(new_env_node(ft_strndup(arg, plus - arg), ft_strdup(plus + 2), true), env);
}

void assign_var(char *arg, t_env **env)
{
	t_env *node;
	char *tmp;
	char *eq;

	eq = ft_strchr(arg, '=');
	node = *env;
	while (node)
	{
		if (ft_strncmp(arg, node->name, ft_strlen(node->name)) == 0
				&& arg + ft_strlen(node->name) == eq)
		{
			tmp = node->value;
			node->value = ft_strndup(arg, eq - arg);
			node->exported = true;
			free(tmp);
			return ;
		}
		node = node->next;
	}
	env_add_last(new_env_node(ft_strndup(arg, eq - arg), ft_strdup(eq + 1), true), env);
}

static int	export_arg(char *arg, t_env **env)
{
	t_mode mode;

	// if one name is not valid return 1, regardless of others
	if (is_valid(arg, &mode) == false)
		return FAILIURE;
	if (mode == EXPORT)
		export_var(arg, env);
	else if (mode == CONCAT)
		concat_var(arg, env);
	else if (mode == ASSIGN)
		assign_var(arg, env);
	return SUCCESS;
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

t_env *dup_env_sorted(t_env *env)
{
	t_env *tmp;
	t_env *node;

	tmp = NULL;
	node = env;
	while (node)
	{
		if (node->value)
			env_add_last(new_env_node(ft_strdup(node->name), ft_strdup(node->value), true), &tmp);
		else
			env_add_last(new_env_node(ft_strdup(node->name), NULL, true), &tmp);
		node = node->next;
	}
	sort_env(&tmp);
	return tmp;
}

int	export_print(t_env *env)
{
	// sort the env in a tmp, then print it
	t_env *sorted;
	t_env *tmp;

	sorted = dup_env_sorted(env);
	tmp = sorted;
	while (sorted)
	{
		printf("declare -x %s", sorted->name);
		if (sorted->value)
			printf("=\"%s\"", sorted->value);
		printf("\n");
		sorted = sorted->next;
	}
	free_env_copy(tmp);
	return SUCCESS;
}

int	export(char **argv, t_env **env)
{
	int i;
	int	ret;

	i = 1;
	if (argv[1] == NULL)
		return (export_print(*env));
	ret = SUCCESS;
	while (argv[i])
	{
		if (export_arg(argv[i++], env) && ret == SUCCESS)
			// print err msg
			ret = FAILIURE;

	}
	return  ret;
}

