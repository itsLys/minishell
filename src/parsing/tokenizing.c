/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 20:32:41 by zbengued          #+#    #+#             */
/*   Updated: 2025/04/18 13:55:18 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "parsing.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void	print_tokens(t_token *tokens)
{
	while (tokens)
	{
		printf("Type: %d", tokens->type);
		if (tokens->val)
			printf(" | Value: %s", tokens->val);
		printf("\n");
		tokens = tokens->next;
	}
}

void	add_token(t_token **head, t_token_type type, const char *value)
{
	t_token	*new;
	t_token	*tmp;

	new = malloc(sizeof(t_token));
	if (!new)
		return ;
	new->type = type;
	if (value)
		new->val = ft_strdup(value);
	else
		new->val = NULL;
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

// NOTE: should check if there is a char that can't be considered as word
void	lexer(char *line, t_token **tokens)
{
	static t_handlers	handle[] = {{'&', handle_and}, {'|', handle_pipe},
	{'>', handle_redir_out}, {'<', handle_redir_in},
	{'(', handle_open_par}, {'*', handle_wildcart},
	{')', handle_close_par}, {'\'', handle_quotes},
	{'\"', handle_quotes}, {'\n', handle_new_cmd}};

	int (i) = 0;
	int (j) = 0;
	while (line[i])
	{
		j = 0;
		while (line[i] && char_in_arr(line[i], " \t"))
			i++;
		while (j < 10)
		{
			if (handle[j].c == line[i])
			{
				handle[j].f(tokens, line, &i);
				break ;
			}
			j++;
		}
		if (j == 10)
			handle_word(tokens, line, &i);
	}
}
