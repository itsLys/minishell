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

void print_vec(char **vec) // NOTE: tester function
{
	int i = 0;
	while (vec[i])
	{
		printf("%d:	|%s|\n", i, vec[i]);
		i++;
	}

}
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
	// print_vec(argv);
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
	return (0);
}
