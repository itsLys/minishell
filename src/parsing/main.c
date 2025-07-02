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

void	add_token(t_token **head, char *type, t_str *value,
		t_token_type t_type)
{
	t_token	*new;
	t_token	*tmp;

	new = malloc(sizeof(t_token));
	if (!new)
		return ;
	new->type = type;
	new->t_type = t_type;
	if (value)
		new->val = str_substr(value, 0, value->size);
	else
		new->val = str_new("");
	new->next = NULL;
	new->prev = NULL;
	if (!*head)
		*head = new;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
	}
}

void	parse_input(char *input, t_token **tokens, t_ast_node **node)
{
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
