/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:38:21 by ihajji            #+#    #+#             */
/*   Updated: 2025/06/24 05:56:37 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	free_resources(char *input, t_token **tokens, t_ast_node **node)
{
	free_tokens(tokens);
	if (*node)
	{
		ast_free(*node);
		*node = NULL;
	}
	free(input);
}

void *free_env(t_env *env)
{
	t_env *tmp;
	while (env)
	{
		// free(env->name);
		// free(env->value);
		// free(env);
		tmp = env->next;
		free_env_node(env);
		env = tmp;
	}
	return NULL;
}
