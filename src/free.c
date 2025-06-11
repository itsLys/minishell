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

#include "minishell.h"
#include "parsing.h"

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

void *free_env_copy(t_env *env_copy)
{
	t_env *tmp;
	while (env_copy)
	{
		tmp = env_copy->next;
		free(env_copy->name);
		free(env_copy->value);
		free(env_copy);
		env_copy = tmp;
	}
	return NULL;
}
