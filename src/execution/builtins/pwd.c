/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:56:52 by ihajji            #+#    #+#             */
/*   Updated: 2025/06/13 16:12:02 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	pwd(char **argv, t_env **env)
{
	char *cwd;

	(void) argv;
	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		cwd = ft_strdup(env_find_var(*env, "PWD")->value);
	if (cwd == NULL)
		return (printf("MAKE ERROR MSG: pwd\n"));
	return printf("%s\n", cwd), free(cwd), SUCCESS;
}
