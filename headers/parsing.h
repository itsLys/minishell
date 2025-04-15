/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 22:25:21 by zbengued          #+#    #+#             */
/*   Updated: 2025/04/15 22:26:29 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

// includes
# include "minishell.h"
# include <readline/history.h>
# include <readline/readline.h>

typedef enum e_token_type
{
	T_WORD,
	T_PIPE,
	T_OR,
	T_AND,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_REDIR_APPEND,
	T_HERDOC,
	T_PAREN_OPEN,
	T_PAREN_CLOSE,
	T_WILDCART,
	T_END,
}	t_token_type;

typedef struct s_token
{
	char			*val;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

void	lexer(char *line, t_token **tokens);
void	print_tokens(t_token *tokens);

#endif // !PARSING_H
