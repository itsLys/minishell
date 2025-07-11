/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 17:29:35 by zbengued          #+#    #+#             */
/*   Updated: 2025/06/30 18:05:13 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parsing.h>
#include <stdio.h>

bool	is_word_or_redir(t_token_type type)
{
	return (is_word(type) || is_redi(type));
}

bool	is_operator(t_token_type type)
{
	return (type < T_PIPE || type > T_AND);
}

size_t	counter(t_token	**tokens, bool mode)
{
	t_token	*act;
	size_t	i;

	i = 0;
	act = *tokens;
	while (mode == WORDS && act && is_word(act->t_type))
	{
		i++;
		act = act->next;
	}
	while (mode == REDIR && act && is_redi(act->t_type))
	{
		i++;
		act = act->next;
	}
	return (i);
}

void	consume_word(t_token **tokens, t_ast_node *args_node)
{
	str_arr_push(&args_node->args, (*tokens)->val.data);
	delete_token(tokens);
}

// NOTE : if heredoc exit with signal should clean_exit
void	consume_redir(t_token **tokens, t_ast_node *red_list)
{
	t_str	filename;

	if ((*tokens)->t_type == T_HERDOC)
	{
		filename = generate_file_name();
		if (run_heredoc((*tokens)->val.data, &filename) == 0)
		{
			free_tokens(tokens);
			return ;
		}
		str_destroy(&(*tokens)->val);
		str_create(&(*tokens)->val, filename.data);
		str_destroy(&filename);
	}
	ast_add_child(red_list,
			ast_new((t_grammar)(*tokens)->t_type, (*tokens)->val.data));
	delete_token(tokens);
	// *tokens = (*tokens)->next;
}
