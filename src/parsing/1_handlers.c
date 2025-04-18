/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_handlers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 10:45:51 by zbengued          #+#    #+#             */
/*   Updated: 2025/04/18 12:31:25 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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
	add_token(tokens, T_LPAR, "(");
	*i += 1;
}
