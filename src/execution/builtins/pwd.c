/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:56:52 by ihajji            #+#    #+#             */
/*   Updated: 2025/06/12 02:47:56 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static char *get_cwd(void)
{
	char *cwd;
	t_data *data;

	data = g_data();
	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		cwd = ft_strdup(fetch_env(data->env_copy, "PWD"));
	return cwd;
}

int	pwd(char **argv)
{
	char *cwd;

	(void) argv;
	cwd = get_cwd();
	if (cwd == NULL)
		return (printf("MAKE ERROR MSG: pwd\n"));
	return printf("%s\n", cwd), SUCCESS;
}
