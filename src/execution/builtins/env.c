/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:55:51 by ihajji            #+#    #+#             */
/*   Updated: 2025/06/13 16:20:48 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int env(char **argv, t_env **env)
{
	(void) argv;
	t_env *tmp;

	tmp = *env;
	while (tmp)
	{
		if (tmp->exported && tmp->value)
			printf("%s=%s\n", tmp->name, tmp->value);
		tmp = tmp->next;
	}
	return SUCCESS;
}
