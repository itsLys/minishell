/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 22:25:21 by zbengued          #+#    #+#             */
/*   Updated: 2025/06/01 08:12:02 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"
# define COLOR_BLUE "\001\033[1;34m\002"
# define COLOR_RESET "\001\033[0m\002"
# define WORDS 0
# define REDIR 1

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
	T_END
}	t_token_type;

typedef enum e_grammar
{
	G_COMPOUND_COMMAND,
	G_PIPELINE,
	G_OR_NODE,
	G_AND_NODE,
	G_REDI_IN,
	G_REDI_TRUNC,
	G_REDI_APPEND,
	G_REDI_HEREDOC,
	G_COMMAND,
	G_ARGS,
	G_SUBSHELL,
	G_SIMPLE_COMMAND,
	G_REDIRECT_LIST,
	G_IO_REDIRECT
}	t_grammar;

typedef struct s_token
{
	char			*val;
	char			*type;
	t_token_type	t_type;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_redirect
{
	t_token_type	type;
	char			*dilimeter;
	char			*filename;
}	t_redirect;

typedef struct s_ast_node
{
	t_grammar			type;	
	char				*value;
	char				**args;
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

// entery point
void		parse_input(char *input, t_token **tokens, t_ast_node **node);

void		print_tokens(t_token *tokens);
void		print_token(t_token *token);
void		free_tokens(t_token **head);
void		pop_token(t_token **tokens, t_token *token);
void		lexer(t_token **tokens, char *line);
void		ast_print_(t_ast_node *node, size_t depth);
void		ast_print(t_ast_node *node,
				size_t depth, const char *prefix, int is_last);
void		ast_free(t_ast_node *node);
void		ast_add_child(t_ast_node *parent, t_ast_node *child);

bool		is_word_or_redir(t_token_type type);
bool		is_redi(t_token_type val);
bool		is_word(t_token_type val);
bool		is_and_or(t_token_type type);
bool		valid_pipe(t_token **tokens);
bool		valid_compound(t_token **tokens);
bool		is_operator(t_token_type type);
size_t		counter(t_token	**tokens, bool mode);
void		consume_word(t_token **tokens, t_ast_node *args_node, size_t *i);
void		consume_redir(t_token **tokens, t_ast_node *red_list);
void		ast_add_child(t_ast_node *parent, t_ast_node *child);
void		trait_redir(t_token **tokens);
void		trait_word(t_token **tokens);

t_ast_node	*ast_new(t_grammar type, char *value);
t_ast_node	*compound_command(t_token **tokens, bool is_subshell);
t_ast_node	*pipeline(t_token **tokens);
t_ast_node	*command(t_token **tokens);
t_ast_node	*simple_command(t_token **tokens);
t_ast_node	*subshell(t_token **tokens);

#endif // !PARSING_H
