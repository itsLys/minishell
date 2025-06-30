/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 07:54:13 by ihajji            #+#    #+#             */
/*   Updated: 2025/06/01 08:02:08 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <execution.h>

void	parse_input(char *input, t_token **tokens, t_ast_node **node)
{
	g_interrupted = 0;
	lexer(tokens, input);
	trait_redir(tokens);
	trait_word(tokens);
	if (*tokens)
		*node = compound_command(tokens, false);
	if (!*node && *tokens)
		printf("SYNTAXE ERROR\n");
	if (*input)
		add_history(input);
}
