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
};

static void	export_arg(char *arg, t_env **env) // must look for the variable if it exist mark it as exported,
							  // else create it, export it;
							  // make a function to add the variable to the env
{
	char **split;
	t_env *node;

	split = ft_split(arg, '=');
	node = env_find_var(*env, split[NAME]);
	if (node)
	{
		node->exported = true;
		if (split[VALUE])
			node->value = split[VALUE];
	}
	else
		env_add_last(new_env_node(split[NAME], split[VALUE], true), env);
}

int	export_print(t_env *env)
{
	// sort the env in a tmp, then print it
	while (env)
	{
		printf("declare -x %s", env->name);
		if (env->value)
			printf("=\"%s\"", env->value);
		printf("\n");
		env = env->next;
	}
	return SUCCESS;
}

int	export(char **argv, t_env **env)
{
	int i;

	i = 1;
	if (argv[1] == NULL)
		return (export_print(*env));
	while (argv[i])
		export_arg(argv[i++], env);
	return  0;
}

