/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:49:52 by ihajji            #+#    #+#             */
/*   Updated: 2025/06/09 18:57:59 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

char *get_path(char **argv, t_data *data)
{

	if (argv[0] && argv[1])
		return NULL;
	// NOTE: ~ should come in the extracted av expanded if not inside "" or ''
	if (argv[0] && ft_strcmp(argv[0], "-") == 0)
		return data->lwd;
	if (argv[0])
		return argv[0];
	// return ft_getenv(data->env_copy, "HOME");
	return NULL;
}

int	cd(char **argv)
{
	char *path;
	t_data *data;

	data = g_data();
	path = get_path(argv + 1, data);
	if (chdir(path))
		return perror("cd"), FAILIURE;
	if (path == data->lwd)
	{
		printf("%s\n", data->lwd);
		free(data->lwd);
		data->lwd = data->cwd;
	}
	data->cwd = getcwd(NULL, 0);
	return SUCCESS;
}
// TODO: implement error messages close to bash
// use av[0] instead of the bare name
