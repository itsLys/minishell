/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 17:53:35 by zbengued          #+#    #+#             */
/*   Updated: 2025/05/19 19:14:00 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parsing.h>

bool	check_quote(char *str)
{
	char	*first_quote_pos;
	char	*quote;
	size_t	i;

	i = 0;
	first_quote_pos = NULL;
	first_quote_pos = ft_strchr(str, '\'');
	if (!first_quote_pos)
		first_quote_pos = ft_strchr(str, '\"');
	if (!first_quote_pos)
		return (true);
	quote = ft_strchr("\'\"", *first_quote_pos);
	while (first_quote_pos[i] && first_quote_pos[i] != *quote)
		i++;
	if (!first_quote_pos[i])
		return (false);
	if (!check_quote(&first_quote_pos[i + 1]))
		return (false);
	return (true);
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
		if (!check_quote(tmp->val))
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

void	free_tokens(t_token **head)
{
	t_token	*next;
	t_token	*tmp;

	if (!head || !*head)
		return ;
	tmp = *head;
	while (tmp)
	{
		next = tmp->next;
		free(tmp->val);
		free(tmp);
		tmp = next;
	}
	*head = NULL;
}
