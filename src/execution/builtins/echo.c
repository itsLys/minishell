/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:45:18 by ihajji            #+#    #+#             */
/*   Updated: 2025/06/13 16:10:10 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static bool	is_n_flaged(char *arg)
{
	int i;

	i = 1;
	if (!arg || arg[0] != '-')
		return false;
	if (arg[i] == 'n')
		i++;
	while (arg[i] == 'n')
		i++;
	return arg[i] == '\0';
}

int	echo(char **argv, t_env **env)
{
	int	n_flaged;
	int	i;

	i = 1;
	n_flaged = 0;
	(void) env;
	while (is_n_flaged(argv[i]))
	{
		n_flaged = 1;
		i++;
	}
	while (argv[i])
	{
		printf("%s", argv[i++]);
		if (argv[i])
			printf(" ");
	}
	if (!n_flaged)
		printf("\n");
	return 0;
}
