/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 20:32:41 by zbengued          #+#    #+#             */
/*   Updated: 2025/04/15 22:09:45 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "parsing.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>


void print_tokens(t_token *tokens)
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

bool	is_whitespace(char str)
{
	return (str == ' ' || str == '\t');
}

bool	char_in_arr(char c, char *arr)
{
	int (i) = 0;
	while (i)
	{
		if (c == arr[i])
			return (true);
		i++;
	}
	return (false);
}

void add_token(t_token **head, t_token_type type, const char *value)
{
	t_token *new;

	new = malloc(sizeof(t_token));
	if (!new)
		return;
	new->type = type;
	if (value)
		new->val = ft_strdup(value);
	else
		new->val = NULL;
	new->next = NULL;
	if (!*head)
		*head = new;
	else
	{
		t_token *tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	handle_pipe(t_token **tokens, char *line, int *i)
{
	if (line[*i + 1] == '|')
	{
		add_token(tokens, T_OR, "||");
		*i += 2;
	}
	else
	{
		add_token(tokens, T_PIPE, "|");
		(*i)++;
	}
}

void	handle_and(t_token **tokens, char *line, int *i)
{
	if (line[*i] == '&' && line[*i + 1] == '&')
	{
		add_token(tokens, T_AND, "&&");
		*i += 2;
	}
}

void	handle_redir_in(t_token **tokens, char *line, int *i)
{
	if (line[*i + 1] == '<')
	{
		add_token(tokens, T_HERDOC, "<<");
		*i += 2;
	}
	else
	{
		add_token(tokens, T_REDIR_IN, "<");
		*i += 1;
	}
}

void	handle_redir_out(t_token **tokens, char *line, int *i)
{
	if (line[*i + 1] == '>')
	{
		add_token(tokens, T_APPEND, ">>");
		*i += 2;
	}
	else
	{
		add_token(tokens, T_REDIR_OUT, ">");
		*i += 1;
	}
}

void	handle_open_par(t_token **tokens, char *line, int *i)
{
	(void)line;
	add_token(tokens, T_PAREN_OPEN, "(");
	*i += 1;
}

void	handle_close_par(t_token **tokens, char *line, int *i)
{
	(void)line;
	add_token(tokens, T_PAREN_CLOSE, ")");
	*i += 1;
}

void	handle_wildcart(t_token **tokens, char *line, int *i)
{
	(void)line;
	add_token(tokens, T_WILDCART, "*");
	*i += 1;
}

void	handle_word(t_token **tokens, char *line, int *i)
{	
	char *word;

	int (start);
	start = *i;
	while (line[*i] && !is_whitespace(line[*i])
		&& !char_in_arr(line[*i], "|><()*"))
		*i += 1;
	word = ft_strndup(&line[start], *i - start);
	add_token(tokens, T_WORD, word);
	free(word);
}

void	lexer(char *line, t_token **tokens)
{	
	static t_handlers handle[] = {{'&', handle_and}, {'|', handle_pipe},
			{'>', handle_redir_out}, {'<', handle_redir_in}, 
			{'(', handle_open_par}, {'*', handle_wildcart},
			{')', handle_close_par}};
	
	int (i) = 0;
	while (line[i]) 
	{
		while (line[i] && is_whitespace(line[i]))
			i++;
		int (j) = 0;
		while (j < 7)
		{
			if (handle[j].c == line[i])
			{
				handle[j].f(tokens, line, &i);
				break;
			}
			j++;
		}
		if (j == 7)
			handle_word(tokens, line, &i);
	}
	add_token(tokens, T_END, NULL);
}
