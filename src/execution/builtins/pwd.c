/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:56:52 by ihajji            #+#    #+#             */
/*   Updated: 2025/06/09 18:57:58 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	pwd(char **argv)
{
	char *cwd;

	cwd = g_data()->cwd;
		return printf("%s\n", cwd), SUCCESS;
	return perror(argv[0]), FAILIURE;
}
