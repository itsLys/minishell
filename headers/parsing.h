/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 22:25:21 by zbengued          #+#    #+#             */
/*   Updated: 2025/04/18 13:57:39 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

// includes
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>

# define COLOR_BLUE "\033[1;34m"
# define COLOR_RESET "\033[0m"

typedef enum e_token_type
{
	T_WORD,
	T_PIPE,
	T_OR,
	T_AND,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_APPEND,
	T_HERDOC,
	T_LPAR,
	T_RPAR,
	T_WILDCART,
	T_INS_DOUB_Q,
	T_INS_SING_Q,
	T_END,
}	t_token_type;

typedef struct s_token
{
	struct s_token	*prev;
	char			*val;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

typedef struct s_handlers
{
	char	c;
	void	(*f)(t_token **, char *, int *);
}	t_handlers;

void	lexer(char *line, t_token **tokens);
void	print_tokens(t_token *tokens);
void	add_token(t_token **head, t_token_type type, const char *value);
void	handle_pipe(t_token **tokens, char *line, int *i);
void	handle_and(t_token **tokens, char *line, int *i);
void	handle_redir_in(t_token **tokens, char *line, int *i);
void	handle_redir_out(t_token **tokens, char *line, int *i);
void	handle_open_par(t_token **tokens, char *line, int *i);
void	handle_close_par(t_token **tokens, char *line, int *i);
void	handle_wildcart(t_token **tokens, char *line, int *i);
void	handle_word(t_token **tokens, char *line, int *i);
void	handle_quotes(t_token **tokens, char *line, int *i);
void	handle_new_cmd(t_token **tokens, char *line, int *i);

#endif // !PARSING_H
