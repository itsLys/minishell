/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:45:18 by ihajji            #+#    #+#             */
/*   Updated: 2025/07/13 12:49:23 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static bool	is_n_flaged(char *arg)
{
	int	i;

	i = 1;
	if (!arg || arg[0] != '-')
		return (false);
	if (arg[i] == 'n')
		i++;
	else
		return (false);
	while (arg[i] == 'n')
		i++;
	return (arg[i] == '\0');
}

int	echo(char **argv, t_env **env, t_data *data)
{
	int	n_flaged;
	int	i;

	(void)data;
	(void)env;
	i = 1;
	n_flaged = 0;
	while (is_n_flaged(argv[i]))
	{
		n_flaged = 1;
		i++;
	}
	while (argv[i])
	{
		ft_putstr_fd(argv[i++], STDOUT_FILENO);
		if (argv[i])
			ft_putstr_fd(" ", STDOUT_FILENO);
	}
	if (!n_flaged)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}
