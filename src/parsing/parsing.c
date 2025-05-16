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
//
// t_ast_node	*consume_redir(t_token **tokens)
// {
// 	t_ast_node	*redir;
// 	t_token		*act;
// 	t_token		*tmp;
//
// 	act = *tokens;
// 	redir = ast_new(G_REDIRECT_LIST, NULL);
// 	while (act)
// 	{
// 		tmp = act->next;
// 		if (act->t_type <= T_HERDOC && act->t_type >= T_REDIRI)
// 		{
			// ast_add_child(redir, ast_new((t_grammar)act->t_type, act->val));
// 			pop_token(tokens, act);
// 			act = tmp;
// 		}
// 		else if (act->t_type == T_WORD)
// 			act = tmp;
// 		else
// 			break ;
// 	}
// 	return (redir);
// }
//
// void	join_and_pop(char *arg, t_token **tokens, t_token *act, t_token *tmp)
// {
// 	t_token	*tmp2;
// 	
// 	while ((*tokens)->t_type != T_WORD)
// 		*tokens = (*tokens)->next;
// 	tmp2 = (*tokens)->next;
// 	arg = ft_strjoin(arg, act->val);
// 	arg = ft_strjoin(arg, ";");
// 	pop_token(tokens, act);
// 	*tokens = tmp2;
// 	act = tmp;
// }
// t_ast_node	*consume_word(t_token **tokens)
// {
// 	t_ast_node	*args;
// 	t_token		*act;
// 	t_token		*tmp;
// 	t_token		*tmp2;
// 	char *arg;
//
// 	arg = NULL;
// 	act = *tokens;
// 	while (act)
// 	{
// 		tmp = act->next;
// 		if (act->t_type == T_WORD)
// 		{
// 			while (*tokens && (*tokens)->t_type != T_WORD)
// 				*tokens = (*tokens)->next;
// 			tmp2 = (*tokens)->next;
// 			arg = ft_strjoin(arg, act->val);
// 			arg = ft_strjoin(arg, ";");
// 			pop_token(tokens, act);
// 			*tokens = tmp2;
// 			act = tmp;
// 		}
// 		else if (act->t_type >= T_REDIRI && act->t_type <= T_APPEND)
// 			act = tmp;
// 		else
// 			break ;
// 	}
// 	args = ast_new(G_ARGS, arg);
// 	return (args);
// }

// t_ast_node	*simple_command(t_token **tokens)
// {
//
// 	red_list = NULL;
// 	arg_list = NULL;
// 	simple_command = ast_new(G_SIMPLE_COMMAND, NULL);
// 	while (*tokens)
// 	{
// 		// printf("HERERE\n");
// 		printf(":::::::::%d\n", (*tokens)->t_type);
// 		if ((*tokens)->t_type == T_WORD)
// 			{arg_list = consume_word(tokens);printf("word consumed\n");}
// 		if (*tokens && (*tokens)->t_type >= T_REDIRI && (*tokens)->t_type <= T_HERDOC)	
// 			{red_list = consume_redir(tokens);printf("redir consumed\n");}
// 		if (*tokens)
// 			break ;
// 	}
// 	if (arg_list)
// 		ast_add_child(simple_command, arg_list);
// 	if (red_list)
// 		ast_add_child(simple_command, red_list);
// 	return (simple_command);
// }

// NOTE : 
// while (tokens are there)
// {
// 	if the token is a word ;
// 		save it in 2d array
// 	else if the token is a redir
// 		create a redir node;
//
// }
//
//
// }

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

void	print_2d_array(char **arr)
{
	int i = 0;

	if (!arr)
		return;

	while (arr[i])
	{
		printf("[%d] %s ", i, arr[i]);
		i++;
	}
	printf("\n");
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
	compound_command_node = compound_command(tokens);
	if (!compound_command_node)
		return (NULL);
	if (!(*tokens))
	{
		printf("SUBSHELL ERROR\n");
		return (NULL);
	}
	*tokens = (*tokens)->next;
	print_tokens(*tokens);
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
	return (NULL);
}

t_ast_node	*pipeline(t_token **tokens)
{
	t_token		*token;
	t_ast_node	*pipes;
	t_ast_node	*command_node;
	
	pipes = ast_new(G_PIPELINE, NULL);
	while(*tokens)
	{
		command_node = command(tokens);
		if (!command_node)
			return (NULL);
		ast_add_child(pipes, command_node);
		token = *tokens;
		if (token && token->t_type == T_PIPE)
			*tokens = (*tokens)->next;
		else
			break ;
	}
	return (pipes);
}

t_ast_node	*compound_command(t_token **tokens)
{
	t_ast_node	*pipes;
	t_ast_node	*compounds;
	t_token		*tmp;
	
	compounds = ast_new(G_COMPOUND_COMMAND, NULL);
	while(*tokens)
	{
		pipes = pipeline(tokens);
		if (!pipes)
			return (NULL);
		ast_add_child(compounds, pipes);
		tmp = *tokens;
		if (tmp && (tmp->t_type == T_OR || tmp->t_type == T_AND))
		{
			ast_add_child(compounds, ast_new((t_grammar)tmp->t_type, NULL));
			*tokens = (*tokens)->next;
		}
		else
			break ;
	}
	return (compounds);
}
