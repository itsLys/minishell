/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:55:51 by ihajji            #+#    #+#             */
/*   Updated: 2025/06/12 02:58:49 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int env(char **argv)
{
	(void) argv;
	t_env *env;

	env = g_data()->env_copy;
	while (env)
	{
		if (env->is_exported)
			printf("%s=%s", env->name, env->value);
		env = env->next;
	}
	return SUCCESS;
}
