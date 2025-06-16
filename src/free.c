/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:38:21 by ihajji            #+#    #+#             */
/*   Updated: 2025/06/10 16:38:39 by ihajji           ###   ########.fr       */
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

void *free_env_copy(t_env *env)
{
	t_env *tmp;
	while (env)
	{
		tmp = env->next;
		free(env->name);
		free(env->value);
		free(env);
		env = tmp;
	}
	return NULL;
}
