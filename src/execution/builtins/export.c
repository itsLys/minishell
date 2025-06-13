/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:56:36 by ihajji            #+#    #+#             */
/*   Updated: 2025/06/12 18:41:09 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	export_print(void)
{
	t_env *env;

	env = g_data()->env_copy;
	while (env)
	{
		printf("declare -x %s", env->name);
		if (env->value)
			printf("=%s\n", env->value);
		env = env->next;
	}
	return SUCCESS;
}

void	export_arg(char *arg) // must look for the variable if it exist mark it as exported,
							  // else create it, export it;
{
	char *eq;
	t_env *env_var;
	char *name;
	char *value;

	eq = ft_strchr(arg, '=');
	env_var = env_find_var(g_data()->env_copy, eq);
	if (eq)
	{
		name = ft_strndup(arg, eq - arg);
		value = ft_strdup(eq + 1);
	}
	else
	{
		name = ft_strdup(arg);
		value = NULL;
	}
	env_add_var(name, value, true);
}

int	export(char **argv)
{
	int i;
	t_env *env;

	i = 0;
	env = g_data()->env_copy;
	if (argv[1] == NULL)
		return (export_print());
	while (argv[i])
		export_arg(argv[i++]);
	return  0;
}

