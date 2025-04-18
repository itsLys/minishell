/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_handlers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 10:47:18 by zbengued          #+#    #+#             */
/*   Updated: 2025/04/18 13:53:09 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "minishell.h"

void	handle_close_par(t_token **tokens, char *line, int *i)
{
	(void)line;
	add_token(tokens, T_RPAR, ")");
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
	char	*word;

	int (start);
	start = *i;
	while (line[*i] && !char_in_arr(line[*i], " \t\n|><()*&\"\'"))
		(*i)++;
	word = ft_strndup(&line[start], *i - start);
	add_token(tokens, T_WORD, word);
	free(word);
}

// TODO : if the quote didn't get closed should write an error
void	handle_quotes(t_token **tokens, char *line, int *i)
{
	char	quote;
	char	*value;

	quote = line[*i];
	*i += 1;
	int (start) = *i;
	while (line[*i] && line[*i] != quote)
		*i += 1;
	if (line[*i] == quote)
	{
		value = ft_strndup(&line[start], *i - start);
		if (quote == '\"')
			add_token(tokens, T_INS_DOUB_Q, value);
		else
			add_token(tokens, T_INS_SING_Q, value);
		free(value);
		*i += 1;
	}
}

void	handle_new_cmd(t_token **tokens, char *line, int *i)
{
	(void)i;
	(void)line;
	(void)tokens;
	add_token(tokens, T_END, NULL);
	*i += 1;
}
