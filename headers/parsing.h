/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 22:25:21 by zbengued          #+#    #+#             */
/*   Updated: 2025/04/24 12:57:58 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

// includes
# include <readline/history.h>
# include <readline/readline.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <libft.h>
# define COLOR_BLUE "\033[1;34m"
# define COLOR_RESET "\033[0m"

typedef enum e_token_type
{
	T_WORD,
	T_PIPE,
	T_OR,
	T_AND,
	T_REDIRI,
	T_REDIRO,
	T_APPEND,
	T_HERDOC,
	T_LPAR,
	T_RPAR,
	T_END,
}	t_token_type;

typedef enum e_grammar
{
	G_COMMAND_LIST,
	G_COMPOUND_LIST,
	G_PIPELINE,
	G_COMMAND,
	G_SUBSHELL,
	G_SIMPLE_COMMAND,
	G_REDIRECT_LIST,
	G_IO_REDIRECT,
}	t_grammar;

typedef struct s_token
{
	char			*val;
	char			*type;
	t_token_type	t_type;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_node
{
	t_grammar	type;	
	char		*cmd;
	t_darr		*arr;	
}	t_node;

typedef struct s_lexem
{
	char			*lexem;
	size_t			tok_len;
	char			*value;
	t_token_type	type;
}	t_lexem;

void	print_tokens(t_token *tokens);
void	free_tokens(t_token **head);
void	lexer(t_token **tokens, char *line);

#endif // !PARSING_H
