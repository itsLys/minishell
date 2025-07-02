/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 20:32:41 by zbengued          #+#    #+#             */
/*   Updated: 2025/07/01 12:40:29 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stdio.h>
#include <unistd.h>

static t_lexem	*init_lexem(void)
{
	static t_lexem	lexem[] = {
	{(t_str){"&&", 2, 2, 0}, "AND", T_AND},
	{(t_str){"||", 2, 2, 0}, "OR", T_OR},
	{(t_str){"<<", 2, 2, 0}, "HERDOC", T_HERDOC},
	{(t_str){">>", 2, 2, 0}, "APPEND", T_APPEND},
	{(t_str){"|", 1, 2, 0}, "PIPE", T_PIPE},
	{(t_str){"<", 1, 2, 0}, "REDI", T_REDIRI},
	{(t_str){">", 1, 2, 0}, "REDO", T_REDIRO},
	{(t_str){"(", 1, 2, 0}, "LPAR", T_LPAR},
	{(t_str){")", 1, 2, 0}, "RPAR", T_RPAR},
	{0}
	};

	return (lexem);
}

static void	append_quoted_segment(t_str *word, t_str *input,
		size_t *i, char quote)
{
	char	current;

	str_append_char(word, quote);
	(*i)++;
	while (*i < input->size)
	{
		current = str_char_at(input, *i);
		str_append_char(word, current);
		(*i)++;
		if (current == quote)
			break ;
	}
}

static size_t	handle_word(t_token **tokens, t_str *input)
{
	t_str	word;
	char	current;
	size_t	i;

	i = 0;
	str_init(&word);
	while (i < input->size)
	{
		current = str_char_at(input, i);
		if (ft_strchr(" \t><|()", current)
			|| str_match(input, "&&", ft_strncmp, i)
			|| str_match(input, "||", ft_strncmp, i))
			break ;
		if (current == '\'' || current == '\"')
			append_quoted_segment(&word, input, &i, current);
		else
		{
			str_append_char(&word, current);
			i++;
		}
	}
	add_token(tokens, "WORD", &word, T_WORD);
	return (str_destroy(&word), i);
}

static void	process_token(t_token **tokens, t_lexem *lexem, t_str *input)
{
	size_t	j;
	t_str	token;

	j = 0;
	while (lexem[j].lexem.data)
	{
		if (input->size >= lexem[j].lexem.size
			&& str_match(input, lexem[j].lexem.data, ft_strncmp, 0))
		{
			token = str_substr(input, 0, lexem[j].lexem.size);
			add_token(tokens, lexem[j].value, &token, lexem[j].type);
			str_shift_by(input, lexem[j].lexem.size);
			str_destroy(&token);
			return ;
		}
		j++;
	}
	if (!ft_strchr(" \t", str_peek(input)))
		str_shift_by(input, handle_word(tokens, input));
}

void	lexer(t_token **tokens, char *line)
{
	t_lexem	*lexem;
	t_str	input;

	input = str_new(line);
	lexem = init_lexem();
	str_shift_while(&input, " \t");
	while (input.size > 0)
	{
		process_token(tokens, lexem, &input);
		str_shift_while(&input, " \t");
	}
	str_destroy(&input);
}
