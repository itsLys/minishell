/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 16:27:18 by zbengued          #+#    #+#             */
/*   Updated: 2025/04/25 19:06:41 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/tilde.h>
#include <stddef.h>
#include <stdlib.h>
// void *return_heap()
// {
// 	static void *heap[64000];
// 	return heap;
// }
//
// void *mem_alloc(int size)
// {
// 	int i  = 0;
//
// 	void **heap = return_heap();
//
// 	while (heap[i])
// 		i++;
// 	void *addr = malloc(size);
// 	if addr == NULL
// 		return NULL
// 	heap[i] = addr;
// 	return addr;
// }

#include "libft.h"
#include <parsing.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

bool	is_word(t_token_type val)
{
	return ((val == T_WORD));
}

bool	is_redi(t_token_type val)
{
	return ((val <= T_HERDOC && val >= T_REDIRI));
}

size_t	counter(t_token	**tokens, bool mode)
{
	t_token	*act;
	size_t	i;
	
	i = 0;
	act = *tokens;
	while (mode == COUNT_WORDS && act && is_word(act->t_type))
	{
		i++;
		act = act->next;
	}
	while (mode == COUNT_REDIR && act && is_redi(act->t_type))
	{
		i++;
		act = act->next;
	}
	return (i);
}

void	consume_word(t_token **tokens, t_ast_node *args_node, size_t *i)
{
	args_node->args[*i] = ft_strdup((*tokens)->val);
	(*i)++;
	*tokens = (*tokens)->next;
}

void	consume_redir(t_token **tokens, t_ast_node *red_list)
{
	ast_add_child(red_list, ast_new((t_grammar)(*tokens)->t_type, (*tokens)->val));
	*tokens = (*tokens)->next;
}

t_ast_node	*simple_command(t_token **tokens)
{
	t_ast_node	*simple_command;
	t_ast_node	*arg_list;
	t_ast_node	*red_list;
	size_t		i;

	i = 0;
	simple_command = ast_new(G_SIMPLE_COMMAND, NULL);
	red_list = ast_new(G_REDIRECT_LIST, NULL);
	arg_list = ast_new(G_ARGS, NULL);
	arg_list->args = ft_calloc(sizeof(char *), (counter(tokens, COUNT_WORDS) + 2));
	if (!arg_list->args)
		return (NULL); // WARN: EXIT
	while (*tokens && (is_word((*tokens)->t_type)|| is_redi((*tokens)->t_type)))
	{
		if (is_word((*tokens)->t_type))
			consume_word(tokens, arg_list, &i);
		else if (*tokens && is_redi((*tokens)->t_type))
			consume_redir(tokens, red_list);
		else if (*tokens && (*tokens)->t_type == T_LPAR)
			return (NULL);
		else if (!(*tokens) || !is_redi((*tokens)->t_type) || !is_word((*tokens)->t_type))
			break ;
	}
	ast_add_child(simple_command, arg_list);
	ast_add_child(simple_command, red_list);
	return (simple_command);
}

t_ast_node	*subshell(t_token **tokens)
{
	t_ast_node	*subshell;
	t_ast_node	*compound_command_node;
	t_ast_node	*red_list;
	
	red_list = ast_new(G_REDIRECT_LIST, NULL);
	subshell = ast_new(G_SUBSHELL, NULL);
	*tokens = (*tokens)->next;
	if (!(*tokens))
		return (NULL); // NOTE : peut etre un parse error (case of there is only '(')
	compound_command_node = compound_command(tokens, true);
	if (!compound_command_node)
		return (NULL);
	if (!(*tokens))
		return (printf("SUBSHELL ERROR\n"), NULL);
	*tokens = (*tokens)->next;
	if (*tokens && is_word((*tokens)->t_type))
		return (NULL);
	while (*tokens &&  is_redi((*tokens)->t_type))
		consume_redir(tokens, red_list);
	ast_add_child(subshell, compound_command_node);
	ast_add_child(subshell, red_list);
	return (subshell);
}

t_ast_node	*command(t_token **tokens)
{
	t_ast_node	*subshell_node;
	t_ast_node	*command;
	t_ast_node	*simple_command_node;

	command = ast_new(G_COMMAND, NULL);
	if (is_word((*tokens)->t_type) || is_redi((*tokens)->t_type))
	{
		simple_command_node = simple_command(tokens);
		if (!simple_command_node)
			return (NULL);
		ast_add_child(command, simple_command_node);
		return (command);
	}
	else if ((*tokens)->t_type == T_LPAR)
	{
		subshell_node = subshell(tokens);
		if (!subshell_node)
			return (NULL);
		ast_add_child(command, subshell_node);
		return (command);
	}
	else if (!(*tokens) && (!((*tokens)->t_type == T_LPAR)
		|| !(is_word((*tokens)->t_type) || is_redi((*tokens)->t_type))))
		return (printf("PARSE ERROR IN COMMAND\n"), NULL);
	return (NULL);
}

bool	valid_pipe(t_token **tokens)
{
	return (is_word((*tokens)->t_type) || is_redi((*tokens)->t_type) 
			|| ((*tokens)->t_type == T_LPAR));
}

t_ast_node	*pipeline(t_token **tokens)
{
	t_ast_node	*pipes;
	t_ast_node	*command_node;
	
	pipes = ast_new(G_PIPELINE, NULL);
	command_node = command(tokens);
	if (!command_node)
		return (NULL);
	ast_add_child(pipes, command_node);
	if (*tokens && (*tokens)->t_type == T_PIPE)
	{
		*tokens = (*tokens)->next;
		if ((*tokens && !valid_pipe(tokens)) || !(*tokens))
			return (printf("PARSE ERROR IN PIPELINE\n"), NULL);
	}
	return (pipes);
}

bool	valid_compound(t_token **tokens)
{
	return ((*tokens)->t_type != T_OR && (*tokens)->t_type != T_AND
				&& (*tokens)->t_type != T_PIPE);
}

t_ast_node	*compound_command(t_token **tokens, bool in_subshell)
{
	t_ast_node	*pipes;
	t_ast_node	*compounds;
	
	compounds = ast_new(G_COMPOUND_COMMAND, NULL);
	while(*tokens)
	{
		pipes = pipeline(tokens);
		if (!pipes && *tokens && (*tokens)->t_type == T_RPAR && in_subshell)
			return (ast_add_child(compounds, pipes), compounds);
		else if (!pipes)
			return (printf("PARSE ERROR \n"), NULL);
		ast_add_child(compounds, pipes);
		if (*tokens && ((*tokens)->t_type == T_OR || (*tokens)->t_type == T_AND))
		{
			ast_add_child(compounds, ast_new((t_grammar)(*tokens)->t_type, NULL));
			*tokens = (*tokens)->next;
			if ((*tokens && !valid_compound(tokens)) || !(*tokens))
				return (printf("PARSE ERROR IN COUMPOUND_COMMAND\n"), NULL);
		}
		else if (*tokens && !in_subshell && (*tokens)->t_type == T_RPAR)
			return (printf("PARSE ERROR IN COUMPOUND_COMMAND\n"), NULL);
	}
	return (compounds);
}
