/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:56:36 by ihajji            #+#    #+#             */
/*   Updated: 2025/06/16 12:31:35 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

// if one name is not valid return 1, regardless of others
static int	export_arg(char *arg, t_env **env)
{
	t_mode	mode;

	if (is_valid(arg, &mode) == false)
		return (FAILIURE);
	if (mode == EXPORT)
		export_var(arg, env);
	else if (mode == CONCAT)
		concat_var(arg, env);
	else if (mode == ASSIGN)
		assign_var(arg, env);
	return (SUCCESS);
}

int	export_print(t_env *env)
{
	t_env	*sorted;
	t_env	*tmp;

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
	free_env(tmp);
	return (SUCCESS);
}

int	export(char **argv, t_env **env, t_data *data)
{
	// printf("arg:	|%s|\n", argv[0]);
	// printf("arg:	|%s|\n", argv[1]);
	int	i;
	int	err;

	(void)data;
	i = 1;
	if (argv[1] == NULL)
		return (export_print(*env));
	err = 0;
	while (argv[i])
	{
		if (export_arg(argv[i], env))
		{
			err = 2;
			ft_dprintf(STDERR, "%s: %s: not a valid identifier\n",
				argv[0], argv[i]);
		}
		i++;
	}
	return (err);
}
