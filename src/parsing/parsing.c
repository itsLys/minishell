/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 16:27:18 by zbengued          #+#    #+#             */
/*   Updated: 2025/05/18 17:59:42 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parsing.h>

// WARN: SHOULD EXIT IN CASE OF CALLOC FAILING
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
	arg_list->args = ft_calloc(sizeof(char *), (counter(tokens, WORDS) + 3));
	if (!arg_list->args)
		return (NULL);
	while (*tokens && is_word_or_redir((*tokens)->t_type))
	{
		if (is_word((*tokens)->t_type))
			consume_word(tokens, arg_list, &i);
		else if (*tokens && is_redi((*tokens)->t_type))
			consume_redir(tokens, red_list);
		else if (!(*tokens) || !is_word_or_redir((*tokens)->t_type))
			break ;
	}
	if (*tokens && (*tokens)->t_type == T_LPAR)
		return (NULL);
	return (ast_add_child(simple_command, arg_list),
		ast_add_child(simple_command, red_list), simple_command);
}

t_ast_node	*subshell(t_token **tokens)
{
	t_ast_node	*subshell;
	t_ast_node	*compound_command_node;
	t_ast_node	*red_list;

	red_list = ast_new(G_REDIRECT_LIST, NULL);
	subshell = ast_new(G_SUBSHELL, NULL);
	*tokens = (*tokens)->next;
	if (!(*tokens) || (*tokens && (!is_word((*tokens)->t_type)
				&& !is_redi((*tokens)->t_type))))
		return (NULL);
	compound_command_node = compound_command(tokens, true);
	if (!compound_command_node)
		return (NULL);
	if (!(*tokens))
		return (NULL);
	*tokens = (*tokens)->next;
	if (*tokens && is_word((*tokens)->t_type))
		return (NULL);
	while (*tokens && is_redi((*tokens)->t_type))
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
		return (NULL);
	return (NULL);
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
			return (NULL);
	}
	return (pipes);
}

t_ast_node	*compound_command(t_token **tokens, bool in_subshell)
{
	t_ast_node	*pipes;
	t_ast_node	*compounds;

	compounds = ast_new(G_COMPOUND_COMMAND, NULL);
	while (*tokens)
	{
		pipes = pipeline(tokens);
		if (!pipes && *tokens && (*tokens)->t_type == T_RPAR
			&& is_operator((*tokens)->t_type) && in_subshell)
			return (ast_add_child(compounds, pipes), compounds);
		else if (!pipes)
			return (NULL);
		ast_add_child(compounds, pipes);
		if (*tokens && is_and_or((*tokens)->t_type))
		{
			ast_add_child(compounds,
				ast_new((t_grammar)(*tokens)->t_type, NULL));
			*tokens = (*tokens)->next;
			if ((*tokens && !valid_compound(tokens)) || !(*tokens))
				return (NULL);
		}
		else if (*tokens && !in_subshell && (*tokens)->t_type == T_RPAR)
			return (NULL);
	}
	return (compounds);
}
