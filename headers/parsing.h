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
	G_COMPOUND_COMMAND,
	G_PIPELINE,
	G_COMMAND,
	G_SUBSHELL,
	G_SIMPLE_COMMAND,
	G_REDIRECT_LIST,
	G_IO_REDIRECT,
	G_AND_NODE,
	G_OR_NODE
}	t_grammar;

typedef struct s_token
{
	char			*val;
	char			*type;
	t_token_type	t_type;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_ast_node
{
	t_grammar	type;	
	char		*value;
	struct s_ast_node	*child;
	struct s_ast_node	*sibling;
}	t_ast_node;

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
void	ast_print_(t_ast_node *node, size_t depth);
void	ast_print(t_ast_node *node, size_t depth, const char *prefix, int is_last);
void	ast_free(t_ast_node *node);
void	ast_add_child(t_ast_node *parent, t_ast_node *child);


void	ast_add_child(t_ast_node *parent, t_ast_node *child);
t_ast_node	*ast_new(t_grammar type, char *value);
void	ast_free(t_ast_node *node);

t_ast_node	*ast_new(t_grammar type, char *value);
t_ast_node	*compound_command(t_token **tokens);
t_ast_node	*pipeline(t_token **tokens);
t_ast_node	*command(t_token **tokens);
t_ast_node	*simple_command(t_token **tokens);
t_ast_node	*subshell(t_token **tokens);

#endif // !PARSING_H
