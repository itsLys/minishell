/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:49:52 by ihajji            #+#    #+#             */
/*   Updated: 2025/06/12 02:45:23 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"


int	cd(char **argv)
{
	// cd arg arg: throws "too many args"
	// cd arg: chdir to arg, or throws err
	// cd: restort to HOME var
	//
	// cd -: chdir to last dir
	// before changing directories, I need to remeber where was I, so to give it to last working directory
	// and I need to know where I am after changing directories
	// and if the  
	char	*dir;
	t_data	*data;

	data = g_data();
	if (argv[1] && argv[2])
		return printf("%s: %s\n", argv[0], "too many arguments"), FAILIURE;
	if (argv[1] == NULL)
	{
		dir = fetch_env(data->env_copy, "HOME");
		if (dir == NULL)
			return printf("%s: %s\n", argv[0], "HOME not set"), FAILIURE;
	}
	else
		dir = argv[1];
	if (chdir(dir) != SUCCESS)
		return perror(argv[0]), FAILIURE; // check errno and print accordingly, I guess
	return SUCCESS;
}
// TODO: implement error messages close to bash
// use av[0] instead of the bare name
// use dprintf instead of pf
