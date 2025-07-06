/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 17:53:35 by zbengued          #+#    #+#             */
/*   Updated: 2025/07/01 12:31:48 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parsing.h>

bool	check_quote(char *str)
{
	bool	in_single;
	bool	in_double;
	int		i;

	i = 0;
	in_single = false;
	in_double = false;
	while (str[i])
	{
		if (str[i] == '\'' && !in_double)
			in_single = !in_single;
		else if (str[i] == '"' && !in_single)
			in_double = !in_double;
		i++;
	}
	return (!in_single && !in_double);
}

void	trait_word(t_token **tokens)
{
	t_token	*tmp;

	tmp = *tokens;
	while (tmp)
	{
		if (!(is_word(tmp->t_type) || is_redi(tmp->t_type)))
		{
			tmp = tmp->next;
			continue ;
		}
		if (!check_quote(tmp->val.data))
		{
			*tokens = NULL;
			printf("SYNTAXE ERROR\n");
			return ;
		}
		tmp = tmp->next;
	}
}

void	trait_redir(t_token **tokens)
{
	t_token	*tmp;

	tmp = *tokens;
	while (tmp)
	{
		if (is_redi(tmp->t_type) && tmp->next && is_word(tmp->next->t_type))
		{
			tmp->val = tmp->next->val;
			pop_token(tokens, tmp->next);
		}
		else if (is_redi(tmp->t_type)
			&& ((tmp->next && !is_word(tmp->next->t_type)) || !tmp->next))
		{
			printf("SYNTAXE ERROR\n");
			*tokens = NULL;
			return ;
		}
		tmp = tmp->next;
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
