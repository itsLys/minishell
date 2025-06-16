/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 12:14:59 by ihajji            #+#    #+#             */
/*   Updated: 2025/06/16 12:18:16 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// WARN: remove
#include "execution.h"

void	print_env(t_env *env)
{
	printf("\n\n::::::::ENVIRONMENT COPY:::::::\n\n");
	printf("| NAME		| VALUE		| EXPORTED?\n");
	while (env)
	{
		printf("| %s		\
				| %s	| %d\n",
			env->name,
			env->value,
			env->exported);
		env = env->next;
	}
}
