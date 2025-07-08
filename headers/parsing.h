/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 22:25:21 by zbengued          #+#    #+#             */
/*   Updated: 2025/07/08 01:28:28 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"
# define COLOR_RESET   "\001\033[0m\002"
# define COLOR_BLUE    "\001\033[1;34m\002"
# define COLOR_RED     "\001\033[31m\002"
# define COLOR_GREEN   "\001\033[32m\002"
# define COLOR_YELLOW  "\001\033[33m\002"
# define COLOR_MAGENTA "\001\033[35m\002"
# define COLOR_CYAN    "\001\033[36m\002"
# define COLOR_WHITE   "\001\033[37m\002"
# define WORDS 0
# define REDIR 1
# define DOUBQ 'D'
# define SINNQ 'S'
# define NONEQ 'N'
# define SCH "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789_-"
# define SAFE_CHARS_LEN 64

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
}						t_token_type;

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
}						t_grammar;

enum					e_node_i
{
	I_COMPOUND_COMMAND,
	I_PIPELINE,
	I_COMMAND,
	I_SUBSHELL,
	I_SIMPLE_COMMAND,
	I_ARGLIST,
	I_RED_LIST
};

typedef struct s_token
{
	t_str				val;
	char				*type;
	t_token_type		t_type;
	struct s_token		*next;
	struct s_token		*prev;
}						t_token;

typedef struct s_ast_node
{
	t_grammar			type;
	t_str				value;
	t_str_arr			args;
	struct s_ast_node	*child;
	struct s_ast_node	*sibling;
}						t_ast_node;

typedef struct s_lexem
{
	t_str				lexem;
	char				*value;
	t_token_type		type;
}						t_lexem;

// entery point
void					parse_input(char *input, t_token **tokens,
							t_ast_node **node);

void					print_tokens(t_token *tokens);
void					print_token(t_token *token);
void					free_tokens(t_token **head);
void					delete_token(t_token **head);
void					pop_token(t_token **tokens, t_token *token);
void					add_token(t_token **head, char *type, t_str *value,
						t_token_type t_type);
void					lexer(t_token **tokens, char *line);
void					ast_print_(t_ast_node *node, size_t depth);
void					ast_print(t_ast_node *node, size_t depth,
							const char *prefix, int is_last);
void					ast_free(t_ast_node *node);
void					free_all_ast(t_ast_node *node);
void					ast_add_child(t_ast_node *parent, t_ast_node *child);

bool					is_word_or_redir(t_token_type type);
bool					is_redi(t_token_type val);
bool					is_word(t_token_type val);
bool					is_and_or(t_token_type type);
bool					valid_pipe(t_token **tokens);
bool					valid_compound(t_token **tokens);
bool					is_operator(t_token_type type);
size_t					counter(t_token **tokens, bool mode);
void					consume_word(t_token **tokens, t_ast_node *args_node);
void					consume_redir(t_token **tokens, t_ast_node *red_list);
void					ast_add_child(t_ast_node *parent, t_ast_node *child);
void					trait_redir(t_token **tokens);
void					trait_word(t_token **tokens);
void					erase(char *str, size_t index);
char					*quote_mask(const char *str);
void					remove_quotes(t_str *str, t_str *mask);

t_ast_node				*ast_new(t_grammar type, char *value);
t_ast_node				*compound_command(t_token **tokens, bool is_subshell);
t_ast_node				*pipeline(t_token **tokens);
t_ast_node				*command(t_token **tokens);
t_ast_node				*simple_command(t_token **tokens);
t_ast_node				*subshell(t_token **tokens);

t_str					generate_file_name(void);
int						run_heredoc(char *delim, t_str *filename);

void					free_resources(char *input, t_token **tokens,
							t_ast_node **node);

#endif // !PARSING_H
