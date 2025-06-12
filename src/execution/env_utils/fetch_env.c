/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fetch_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 00:05:19 by ihajji            #+#    #+#             */
/*   Updated: 2025/06/12 00:05:35 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

char *fetch_env(t_env *env, char *var)
{
	// edge cases env==NULL, var=NULL
	int len;

	len = ft_strlen(var);
	while (env)
	{
		if (ft_strncmp(env->name, var, len) == 0)
			return (env->value);
		env = env->next;
	}
	return NULL;
	// if want to modify value duplicate it
}
