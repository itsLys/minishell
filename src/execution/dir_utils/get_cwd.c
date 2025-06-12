/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 00:39:57 by ihajji            #+#    #+#             */
/*   Updated: 2025/06/12 01:47:09 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

char *get_cwd(void)
{
	char *cwd;
	t_data *data;

	data = g_data();
	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		cwd = ft_strdup(fetch_env(data->env_copy, "PWD"));
	return cwd;
}

