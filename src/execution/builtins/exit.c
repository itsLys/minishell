/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:56:20 by ihajji            #+#    #+#             */
/*   Updated: 2025/06/21 11:30:20 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	ft_exit(char **argv, t_env **env, t_data *data)
{
	(void)argv;
	(void)env;
	if (argv[1] && argv[2])
		print_error(argv[0], "too many arguments");
	free_env_copy(data->env);
	free(data->input);
	// free(data);
	if (argv[1] && ft_strisnum(argv[1]) == false)
		print_error(argv[0], "numeric argument required");
	else if (argv[1])
		exit(ft_atol(argv[1]) % 256);
	else
		exit(0); // exit with last exit status that is cached
	exit(2);
}
