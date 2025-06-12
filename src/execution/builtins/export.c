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
	}

}

int	export(char **argv)
{
	if (argv[1] == NULL)
		return (export_print());
}

