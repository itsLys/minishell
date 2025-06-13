/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:46:39 by ihajji            #+#    #+#             */
/*   Updated: 2025/06/12 02:48:20 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

t_builtin	*init_builtins(void)
{
	static t_builtin builtin[] = {
		{"echo", &echo},
		{"cd", &cd},
		{"pwd", &pwd},
		{"export", &export},
		{"unset", &unset},
		{"env", &env},
		{"exit", &ft_exit},
		{0},
	};
	return builtin;
}

t_builtin	*find_builtin(char *cmd)
{
	int i = 0;
	t_builtin *table;

	table = init_builtins();
	while (table[i].name)
	{
		if (ft_strcmp(cmd, table[i].name) == 0)
			return &table[i];
		i++;
	}
	return NULL;
}
