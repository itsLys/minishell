/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:57:22 by ihajji            #+#    #+#             */
/*   Updated: 2025/07/13 12:46:58 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	unset_var(char *arg, t_env **env)
{
	t_env	*node;

	node = env_find_var(*env, arg);
	if (node == NULL)
		return ;
	env_remove_node(node, env);
}

int	unset(char **argv, t_env **env, t_data *data)
{
	int	i;

	i = 1;
	(void)data;
	while (argv[i])
		unset_var(argv[i++], env);
	return (SUCCESS);
}
