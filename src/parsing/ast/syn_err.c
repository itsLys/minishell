/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syn_err.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 15:55:54 by zbengued          #+#    #+#             */
/*   Updated: 2025/07/10 15:56:04 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parsing.h>

void	syntax_err(t_token **tokens, t_ast_node *node)
{
	g_interrupted[2] = 2;
	ft_dprintf(STDERR, "minishell : Syntax error\n");
	free_tokens(tokens);
	*tokens = NULL;
	free_all_ast(node);
}
