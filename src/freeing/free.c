/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:38:21 by ihajji            #+#    #+#             */
/*   Updated: 2025/07/03 19:07:37 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	free_resources(char *input, t_token **tokens, t_ast_node **node)
{
	free_tokens(tokens);
	if (*node)
	{
		free_all_ast(*node);
		*node = NULL;
	}
	free(input);
}

void	*free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		free_env_node(env);
		env = tmp;
	}
	return (NULL);
}

void	free_data(t_data *data)
{
	free_env(data->env);
	free(data->input);
	free(data->oldpwd);
	free(data->pwd);
}

void	clean_exit(unsigned int status, t_data *data)
{
	free_all_ast(data->ast);
	free_tokens(&(data->tokens));
	free_data(data);
	exit(status);
}
