/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:56:20 by ihajji            #+#    #+#             */
/*   Updated: 2025/07/13 12:48:38 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	ft_exit(char **argv, t_env **env, t_data *data)
{
	int	status;

	(void)argv;
	(void)env;
	if (argv[1] && ft_strisnum(argv[1]) == false)
	{
		print_error(argv[0], "numeric argument required");
		ft_free_vector(argv);
		clean_exit(2, data);
	}
	if (argv[1] && argv[2])
		return (print_error(argv[0], "too many arguments"), FAILIURE);
	else if (argv[1])
		status = ft_atol(argv[1]) % 256;
	else
		status = g_interrupted[2];
	ft_free_vector(argv);
	clean_exit(status, data);
	return (SUCCESS);
}
