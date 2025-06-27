/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 20:32:41 by zbengued          #+#    #+#             */
/*   Updated: 2025/05/19 18:30:26 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stdio.h>
#include <unistd.h>

// static void	add_token(t_token **head, char *type,
// 		t_str *value, t_token_type t_type)
// {
// 	t_token	*new;
// 	t_token	*tmp;
//
// 	new = malloc(sizeof(t_token));
// 	if (!new)
// 		return ;
// 	new->type = type;
// 	new->t_type = t_type;
// 	if (value)
// 		new->val = ft_strdup(value);
// 	else
// 		new->val = NULL;
// 	new->next = NULL;
// 	new->prev = NULL;
// 	if (!*head)
// 		*head = new;
// 	else
// 	{
// 		tmp = *head;
// 		while (tmp->next)
// 			tmp = tmp->next;
// 		tmp->next = new;
// 		new->prev = tmp;
// 	}
// }
static void	add_token(t_token **head, char *type, t_str *value, t_token_type t_type)
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
		new->val = str_new("");     // ou une version vide
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

void	pop_token(t_token **tokens, t_token *token)
{
	t_token	*prev;
	t_token	*next;

	if (!token)
		return ;
	prev = token->prev;
	next = token->next;
	if (prev)
		prev->next = next;
	else
		*tokens = next;
	if (next)
		next->prev = prev;
	free(token);
}

static size_t	handle_word(t_token **tokens, char *line)
{
	char	*word;
	char	*c ;
	size_t	i;

	i = 0;
	while (line[i] && !ft_strchr(" \t><|()", line[i]))
	{
		if (!ft_strncmp(&line[i], "&&", 2))
			break ;
		c = ft_strchr("\'\"", line[i]);
		if (c)
		{
			i++;
			while (line[i] && *c != line[i])
				i++;
			if (*c == line[i])
				i++;
			continue ;
		}
		i++;
	}
	word = ft_strndup(line, i);
	add_token(tokens, "WORD", word, T_WORD);
	free(word);
	return (i);
}

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

// void	lexer_(t_token **tokens, char *line)
// {
// 	t_lexem		*lexem;
// 	size_t		i;
// 	size_t		j;
//
// 	i = 0;
// 	lexem = init_lexem();
// 	while (line[i])
// 	{
// 		while (line[i] && ft_strchr(" \t", line[i]))
// 			i++;
// 		j = 0;
// 		while (lexem[j].lexem)
// 		{
// 			if (!ft_strncmp(&line[i], lexem[j].lexem, lexem[j].tok_len))
// 			{
// 				add_token(tokens, lexem[j].value,
// 					lexem[j].lexem, lexem[j].type);
// 				i += lexem[j].tok_len;
// 				break ;
// 			}
// 			j++;
// 		}
// 		if (!lexem[j].lexem && !ft_strchr(" \t", line[i]))
// 			i += handle_word(tokens, &line[i]);on to access this resource.
// 	}
// }

void	lexer(t_token **tokens, char *line)
{
	t_lexem		*lexem = init_lexem();
	t_str		input;
	t_str		token;
	size_t		j;

	input = str_new(line);
	str_shift_while(&input, " \t");
	while (input.size > 0)
	{
		j = 0;
		while (lexem[j].lexem.data)
		{
			if (input.size >= lexem[j].lexem.size &&
				str_match(&input, lexem[j].lexem.data, ft_strncmp, 0))
			{
				token = str_substr(&input, 0, lexem[j].lexem.size);
				add_token(tokens, lexem[j].value, &token, lexem[j].type);
				str_shift_by(&input, lexem[j].lexem.size);
				str_destroy(&token);
				break ;
			}
			j++;
		}
		if (!lexem[j].lexem.data && !ft_strchr(" \t", str_peek(&input)))
			str_shift_by(&input, handle_word(tokens, input.data));
		str_shift_while(&input, " \t");
	}
	str_destroy(&input);
}
